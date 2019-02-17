#include "stdafx.h"
#include <string>
#include <iostream>
#include <cassert>
#include <ctime>

using namespace std;

struct Record
{
	const int value;
	string name;

	Record(int value) : value(value)
	{}

	Record(int value, string str) : value(value), name(str)
	{}

	operator int() const
	{
		return value;
	}
};

template <class T>
class BST
{

public:
	BST() : root(nullptr)
	{}

	BST(T value) : root(new Node{ value, nullptr, nullptr })
	{}

	~BST()
	{
		deleteLeftRightNode(root);
	}

	void insert(const T& value)
	{
		addNode(root, value);
	}

	void printSorted()
	{
		goLeftNodeRight(root);
		cout << endl;
	}

	T& search(int value)
	{
		return searchNode(root, value)->value;
	}

	T& getMin()
	{
		return getMinNode(root)->value;
	}

	T& getMax()
	{
		return getMaxNode(root)->value;
	}

	void remove(int value)
	{
		Node* nodeToDelete = searchNode(root, value);
		if (!nodeToDelete)
			return;
		Node* parentNode = getParentNode(nodeToDelete, root);

		Node* maxNode;
		if(!nodeToDelete->left)
			maxNode = getMaxNode(nodeToDelete->right);
		else
			maxNode = getMaxNode(nodeToDelete->left);
		
		Node* maxNodeParent = getParentNode(maxNode, nodeToDelete);

		disconnect(parentNode, nodeToDelete);
		disconnect(maxNodeParent, maxNode);

		if (maxNode)
		{
			connect(maxNodeParent, maxNode->left);
			connect(maxNodeParent, maxNode->right);
			disconnect(maxNode, maxNode->left);
			disconnect(maxNode, maxNode->right);
		}

		connect(parentNode, maxNode);
		connect(maxNode, nodeToDelete->left);
		connect(maxNode, nodeToDelete->right);
		
		delete nodeToDelete;
	}

	void clear()
	{
		deleteLeftRightNode(root);
	}

private:
	struct Node
	{
		T value;
		Node* left;
		Node* right;
	};

	Node* root;

	void addNode(Node* node, const T& value)
	{
		if (!node)
			root = new Node{ value, nullptr, nullptr };
		else if (value < node->value)
		{
			if (!node->left)
				node->left = new Node{ value, nullptr, nullptr };
			else
				addNode(node->left, value);
		}
		else if (value >= node->value)
		{
			if (!node->right)
				node->right = new Node{ value, nullptr, nullptr };
			else
				addNode(node->right, value);
		}
	}

	void goLeftNodeRight(Node* node)
	{
		if (!node)
			return;
		goLeftNodeRight(node->left);
		cout << node->value << "  ";
		goLeftNodeRight(node->right);
	}

	void deleteLeftRightNode(Node* node)
	{
		if (!node)
			return;
		deleteLeftRightNode(node->left);
		deleteLeftRightNode(node->right);
		delete node;
		if (node == root)
			root = nullptr;
	}

	Node* searchNode(Node* node, int value)
	{
		if (!node)
			return nullptr;
		if (value == node->value)
			return node;
		if (value < node->value)
			return searchNode(node->left, value);
		if (value > node->value)
			return searchNode(node->right, value);
	}

	Node* getMinNode(Node* node)
	{
		if (!node)
			return nullptr;
		if (!node->left)
			return node;
		return getMinNode(node->left);
	}

	Node* getMaxNode(Node* node)
	{
		if (!node)
			return nullptr;
		if (!node->right)
			return node;
		return getMaxNode(node->right);
	}

	Node* getParentNode(Node* childNode, Node* node)
	{
		if (childNode == root)
			return nullptr;
		if (node->left == childNode || node->right == childNode)
			return node;
		if (childNode->value < node->value)
			return getParentNode(childNode, node->left);
		if (childNode->value > node->value)
			return getParentNode(childNode, node->right);
	}

	void connect(Node* parent, Node* child)
	{
		if (!child)
			return;

		if (!parent)
		{
			root = child;
			return;
		}
		
		if (child->value < parent->value && !parent->left)
			parent->left = child;
		else if (child->value >= parent->value && !parent->right)
			parent->right = child;
	}

	void disconnect(Node* parent, Node* child)
	{
		if (!parent)
			return;

		if (parent->left == child)
			parent->left = nullptr;
		else if (parent->right = child)
			parent->right = nullptr;
	}
	
};


int main()
{
	srand(time(0));

	BST<Record> tree(Record(9,	"A"));
    tree.insert(Record(3,		"B"));
	tree.insert(Record(10,		"C"));
	tree.insert(Record(2,		"D"));
	tree.insert(Record(7,		"E"));
	tree.insert(Record(1,		"F"));
	tree.insert(Record(12,		"G"));
	tree.insert(Record(6,		"H"));
	tree.insert(Record(11,		"I"));
	tree.insert(Record(14,		"J"));

	tree.printSorted();
	tree.search(12).name = "Q";
	cout << tree.search(12).name << endl;
	cout << tree.getMin() << endl << tree.getMax() << endl;
	 
	tree.remove(14);
	tree.printSorted();

	tree.clear();
	for (int i = 0; i < 20; i++)
		tree.insert(Record(rand() % 100));
	tree.printSorted();

	cout << tree.getMin() << endl << tree.getMax() << endl;

	for (int i = 0; i < 70; i++)
		tree.remove(rand() % 100);
	tree.printSorted();

	cout << tree.getMin() << endl << tree.getMax() << endl;

	system("pause");
	return 0;
}
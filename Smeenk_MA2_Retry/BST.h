#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <limits>
#include <vector>
#include <queue>
using namespace std;


/* ----------------------------------------------------------------------------
---- Below is declaration of BST class, referring to textbook, Figure 4.16 ----
---------------------------------------------------------------------------- */

template <typename Comparable>
class BST
{
public:
	BST();
	~BST();
	void makeEmpty();

	const Comparable& findMin() const;
	const Comparable& findMax() const;

	bool contains(const Comparable& x) const;
	void insert(const Comparable& x);
	void remove(const Comparable& x);
	int treeSize() const;
	int treeHeight() const;
	void printInOrder() const;
	void printLevels() const;
	void printMaxPath() const;

private:
	struct BinaryNode
	{
		Comparable element;
		BinaryNode* left;
		BinaryNode* right;

		BinaryNode(const Comparable& theElement, BinaryNode* lt, BinaryNode* rt) : element(theElement), left(lt), right(rt) {}
		BinaryNode(Comparable&& theElement, BinaryNode* lt, BinaryNode* rt) : element(move(theElement)), left(lt), right(rt) {}
	};

	BinaryNode* root;

	BinaryNode* findMin(BinaryNode* t) const;
	BinaryNode* findMax(BinaryNode* t) const;
	void makeEmpty(BinaryNode*& t);

	int treeSize(BinaryNode* node) const;
	void printCurrentLevel(BinaryNode* node, int level) const;
};


/* --------------------------------------------------------------
---- Below is implementation of public and private functions ----
-------------------------------------------------------------- */

// constructor
template<typename Comparable>
BST<Comparable>::BST() : root(NULL) {}

// destructor, refer to textbook, Figure 4.27
template<typename Comparable>
BST<Comparable>::~BST() {
	makeEmpty();
}

// public makeEmpty: refer to textbook, Figure 4.27
template <typename Comparable>
void BST<Comparable>::makeEmpty() {
	makeEmpty(root);
}

// private recursive makeEmpty: refer to textbook, Figure 4.27
template <typename Comparable>
void BST<Comparable>::makeEmpty(BinaryNode*& t) {
	if (t != NULL) {
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
		t = NULL;
	}
}

// // public findMin
template <typename Comparable>
const Comparable& BST<Comparable>::findMin() const {
	if (root == NULL) {
		throw underflow_error("Tree is empty");
	}
	return findMin(root)->element;
}

// private findMin: refer to textbook, Figure 4.20
template <typename Comparable>
typename BST<Comparable>::BinaryNode* BST<Comparable>::findMin(BinaryNode* t) const {
	if (t == NULL) {
		return NULL;
	}
	else if (t->left == NULL) {
		return t;
	}
	else {
		return findMin(t->left);
	}
}

// public findMax
template <typename Comparable>
const Comparable& BST<Comparable>::findMax() const {
	if (root == NULL) {
		throw underflow_error("Tree is empty");
	}
	return findMax(root)->element;
}

// private findMax: refer to textbook, Figure 4.21
template <typename Comparable>
typename BST<Comparable>::BinaryNode* BST<Comparable>::findMax(BinaryNode* t) const {
	if (t == NULL) {
		return NULL;
	}
	else if (t->right == NULL) {
		return t;
	}
	else {
		return findMax(t->right);
	}
}

// public contains: refer to textbook, Figure 4.17, Line 4 - 7
template<typename Comparable>
bool BST<Comparable>::contains(const Comparable& x) const {
	BinaryNode* t = root;

	while (t != nullptr) 
	{
		if (x < t->element) 
		{
			t = t->left;
		}
		else if (x > t->element) 
		{
			t = t->right;
		}
		else {
			return true;
		}
	}

	return false;
}

// public insert: refer to textbook, Figure 4.17, Line 12 - 15
template<typename Comparable>
void BST<Comparable>::insert(const Comparable& x) {
	if (root == nullptr)
	{
		root = new BinaryNode(x, nullptr, nullptr);
	}
	else
	{
		BinaryNode* current = root;
		BinaryNode* previous = nullptr;

		while (current != nullptr)
		{
			previous = current;

			if (x < current->element)
			{
				current = current->left;
			}
			else if (x > current->element)
			{
				current = current->right;
			}
			else
			{
				cout << "Already found in the tree" << endl;
				return;
			}
		}

		if (x < previous->element)
		{
			previous->left = new BinaryNode(x, nullptr, nullptr);
		}
		else
		{
			previous->right = new BinaryNode(x, nullptr, nullptr);
		}
	}
}

// public remove: refer to textbook, Figure 4.17, Line 20 - 23
template<typename Comparable>
void BST<Comparable>::remove(const Comparable& x) {
	BinaryNode* current = root;
	BinaryNode* previous = nullptr;

	while (current != nullptr && current->element != x)
	{
		previous = current;
		if (x < current->element)
		{
			current = current->left;
		}
		else
		{
			current = current->right;
		}
	}

	if (current->left != nullptr && current->right != nullptr)
	{
		BinaryNode* nextNode = current->right;
		BinaryNode* nextNodeParent = current;

		while (nextNode->left != nullptr)
		{
			nextNodeParent = nextNode;
			nextNode = nextNode->left;
		}

		current->element = nextNode->element;

		current = nextNode;
		previous = nextNodeParent;
	}

	BinaryNode* child = nullptr;

	if (current->left != nullptr)
	{
		child = current->left;
	}
	else if (current->right != nullptr)
	{
		child = current->right;
	}

	if (current == root)
	{
		root = child;
	}
	else if (previous->left == current)
	{
		previous->left = child;
	}
	else
	{
		previous->right = child;
	}

	delete current;
}

// public treeSize
template <typename Comparable>
int BST<Comparable>::treeSize() const {
	if (root == nullptr)
	{
		return 0;
	}

	return treeSize(root);
}

// public treeHeight
template <typename Comparable>
int BST<Comparable>::treeHeight() const {
	if (root == nullptr)
	{
		return -1;
	}

	BinaryNode* current = root;
	int maxHeight = 0;
	int currentHeight = 0;

	while (current != nullptr)
	{
		if (current->left == nullptr)
		{
			currentHeight++;
			if (currentHeight > maxHeight)
			{
				maxHeight = currentHeight;
			}
			current = current->right;
		}
		else
		{
			BinaryNode* traverser = current->left;

			int level = 1;

			while (traverser->right != nullptr && traverser->right != current)
			{
				traverser = traverser->right;
				level++;
			}

			if (traverser->right == nullptr)
			{
				traverser->right = current;
				current = current->left;
				currentHeight++;
			}
			else
			{
				traverser->right = nullptr;
				currentHeight -= level;
				current = current->right;
			}
		}
	}

	return maxHeight - 1;
}

// public printInOrder: refer to textbook, Figure 4.60
template<typename Comparable>
void BST<Comparable>::printInOrder() const {
	BinaryNode* current = root;

	if (current == nullptr)
	{
		return;
	}

	if (current->left != nullptr)
	{
		BST<Comparable> leftTree;
		leftTree.root = current->left;
		leftTree.printInOrder();
	}

	cout << current->element << " ";

	if (current->right != nullptr)
	{
		BST<Comparable> rightTree;
		rightTree.root = current->right;
		rightTree.printInOrder();
	}
}

// public printLevels
template <typename Comparable>
void BST<Comparable>::printLevels() const {
	if (root == nullptr)
	{
		return;
	}

	int height = treeHeight();

	for (int level = 0; level <= height; level++)
	{
		printCurrentLevel(root, level);
		cout << endl;
	}
}

// public printMaxPath
template <typename Comparable>
void BST<Comparable>::printMaxPath() const {
	if (root == nullptr)
	{
		return;
	}

	BinaryNode* current = root;

	while (current != nullptr)
	{
		cout << current->element << " ";

		int leftHeight = 0;
		int rightHeight = 0;

		BinaryNode* leftTree = current->left;
		BinaryNode* rightTree = current->right;

		while (leftTree != nullptr)
		{
			int leftTreeLeftHeight = 0;
			int leftTreeRightHeight = 0;

			if (leftTree->left != nullptr)
			{
				BinaryNode* temp = leftTree->left;

				while (temp != nullptr)
				{
					leftTreeLeftHeight++;
					temp = temp->left;
				}
			}
			if (leftTree->right != nullptr)
			{
				BinaryNode* temp = leftTree->right;

				while (temp != nullptr)
				{
					leftTreeRightHeight++;
					temp = temp->right;
				}
			}

			leftHeight++;

			if (leftTreeLeftHeight > leftTreeRightHeight)
			{
				leftTree = leftTree->left;
			}
			else
			{
				leftTree = leftTree->right;
			}
		}

		while (rightTree != nullptr)
		{
			int rightTreeLeftHeight = 0;
			int rightTreeRightHeight = 0;

			if (rightTree->left != nullptr)
			{
				BinaryNode* temp = rightTree->left;

				while (temp != nullptr)
				{
					rightTreeLeftHeight++;
					temp = temp->left;
				}
			}
			if (rightTree->right != nullptr)
			{
				BinaryNode* temp = rightTree->right;

				while (temp != nullptr)
				{
					rightTreeRightHeight++;
					temp = temp->right;
				}
			}

			rightHeight++;

			if (rightTreeLeftHeight > rightTreeRightHeight)
			{
				rightTree = rightTree->left;
			}
			else
			{
				rightTree = rightTree->right;
			}
		}

		if (leftHeight > rightHeight)
		{
			current = current->left;
		}
		else
		{
			current = current->right;
		}
	}

	cout << endl;

}

template <typename Comparable>
int BST<Comparable>::treeSize(BinaryNode* node) const {
	if (node == nullptr)
	{
		return 0;
	}

	return 1 + treeSize(node->left) + treeSize(node->right);
}

template<typename Comparable>
void BST<Comparable>::printCurrentLevel(BinaryNode* node, int level) const {
	if (node == nullptr)
	{
		return;
	}

	if (level == 0)
	{
		cout << node->element << " ";
	}
	else
	{
		printCurrentLevel(node->left, level - 1);
		printCurrentLevel(node->right, level - 1);
	}
}

#endif
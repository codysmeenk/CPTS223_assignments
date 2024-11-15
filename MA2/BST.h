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

	const Comparable & findMin() const;
	const Comparable & findMax() const;

	bool contains(const Comparable & x) const;
	void insert(const Comparable & x);
	void remove(const Comparable & x);
	int treeSize() const;
	int treeHeight() const;
	void printInOrder() const;
	void printLevels() const;
	void printMaxPath() const;

private:
	struct BinaryNode
	{
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;

		BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt): element(theElement), left(lt), right(rt) {}
		BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt): element(move(theElement)), left(lt), right(rt) {}
	};

	BinaryNode *root;

	BinaryNode * findMin( BinaryNode * t ) const;
	BinaryNode * findMax( BinaryNode * t ) const;
	void makeEmpty( BinaryNode * & t );
	void remove(const Comparable& x, BinaryNode*& t);
	int treeSize(BinaryNode* t) const;
	int treeHeight(BinaryNode* t) const;
	void printInOrder(BinaryNode* t, bool &isFirst) const;
	void printMaxPath(BinaryNode* t) const;
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
void BST<Comparable>::makeEmpty(BinaryNode *& t) {
    if ( t != NULL ) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = NULL;
    }
}

template<typename Comparable>
inline void BST<Comparable>::remove(const Comparable& x, BinaryNode*& t)
{
	if (t == nullptr) {
		return;
	}

	if (x < t->element) {
		remove(x, t->left);
	}
	else if (t->element < x) {
		remove(x, t->right);
	}
	else if (t->left != nullptr && t->right != nullptr) {
		t->element = findMin(t->right)->element;

		remove(t->element, t->right);
	}
	else {
		BinaryNode* oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right;
		delete oldNode;
	}
}

template<typename Comparable>
inline int BST<Comparable>::treeSize(BinaryNode* t) const
{
	if (t == nullptr) {
		return 0;
	}

	return 1 + treeSize(t->left) + treeSize(t->right);
}

template<typename Comparable>
inline int BST<Comparable>::treeHeight(BinaryNode* t) const
{
	if (t == nullptr) {
		return -1;
	}

	return 1 + max(treeHeight(t->left), treeHeight(t->right));
}

template<typename Comparable>
inline void BST<Comparable>::printInOrder(BinaryNode* t, bool &isFirst) const
{
	if (t != nullptr) {
		printInOrder(t->left, isFirst);

		if (!isFirst) {
			std::cout << " -> ";
		}
		std::cout << t->element;
		isFirst = false;

		printInOrder(t->right, isFirst);
	}
}

template<typename Comparable>
inline void BST<Comparable>::printMaxPath(BinaryNode* t) const
{
	if (t != nullptr) {
		std::cout << t->element;

		if (t->left != nullptr || t->right != nullptr) {
			std::cout << " -> ";
		}

		if (treeHeight(t->left) >= treeHeight(t->right)) {
			printMaxPath(t->left);
		}
		else {
			printMaxPath(t->right);
		}
	}
}

// // public findMin
template <typename Comparable>
const Comparable & BST<Comparable>::findMin() const {
    if (root == NULL) {
    	throw underflow_error("Tree is empty");
	}
    return findMin(root)->element;
}

// private findMin: refer to textbook, Figure 4.20
template <typename Comparable>
typename BST<Comparable>::BinaryNode* BST<Comparable>::findMin(BinaryNode * t) const {
    if ( t == NULL ) {
        return NULL;
    } else if (t->left == NULL) {
        return t;
    } else {
        return findMin(t->left);
    }
}

// public findMax
template <typename Comparable>
const Comparable & BST<Comparable>::findMax() const {
    if (root == NULL) {
    	throw underflow_error("Tree is empty");
	}
    return findMax(root)->element;
}

// private findMax: refer to textbook, Figure 4.21
template <typename Comparable>
typename BST<Comparable>::BinaryNode* BST<Comparable>::findMax(BinaryNode * t) const {
    if ( t == NULL ) {
        return NULL;
    } else if (t->right == NULL) {
        return t;
    } else {
        return findMin(t->right);
    }
}

// public contains: refer to textbook, Figure 4.17, Line 4 - 7
template<typename Comparable>
bool BST<Comparable>::contains( const Comparable & x ) const {
	BinaryNode* current = root;

	while (current != nullptr) {
		if (x < current->element) {
			current = current->left;
		}
		else if (current->element < x) {
			current = current->right;
		}
		else {
			return true;
		}
	}
	return false;
}

// public insert: refer to textbook, Figure 4.17, Line 12 - 15
template<typename Comparable>
void BST<Comparable>::insert(const Comparable & x) {
	BinaryNode** current = &root;

	while (*current != nullptr) {
		if (x < (*current)->element) {
			current = &(*current)->left;
		}
		else if ((*current)->element < x) {
			current = &(*current)->right;
		}
		else {
			return;
		}
	}

	*current = new BinaryNode{ x, nullptr, nullptr };
}


// public remove: refer to textbook, Figure 4.17, Line 20 - 23
template<typename Comparable>
void BST<Comparable>::remove( const Comparable & x ) {
	remove(x, root);
}

// public treeSize
template <typename Comparable>
int BST<Comparable>::treeSize() const {
	return treeSize(root);
}

// public treeHeight
template <typename Comparable>
int BST<Comparable>::treeHeight() const {
	return treeHeight(root);
}

// public printInOrder: refer to textbook, Figure 4.60
template<typename Comparable>
void BST<Comparable>::printInOrder() const {
	if (root == nullptr) {
		std::cout << "Empty tree" << std::endl;
	}
	else {
		bool isFirst = true;
		printInOrder(root, isFirst);
		std::cout << " </s>" << std::endl;
	}
}

// public printLevels
template <typename Comparable>
void BST<Comparable>::printLevels() const {
	if (root == nullptr) {
		std::cout << "Empty Tree" << std::endl;
		return;
	}

	std::queue<std::pair<BinaryNode*, int>> q;
	q.push({root, 0});
	int currentLevel = 0;

	std::cout << "Level 0: ";

	while (!q.empty()) {
		BinaryNode* current = q.front().first;
		int level = q.front().second;
		q.pop();

		if (level != currentLevel) {
			currentLevel = level;
			std::cout << std::endl << "Level " << currentLevel << ": ";
		}

		std::cout << current->element << " ";

		if (current->left != nullptr) {
			q.push({ current->left, level + 1 });
		}
		if (current->right != nullptr) {
			q.push({ current->right, level + 1 });
		}
	}

	std::cout << std::endl;
}

// public printMaxPath
template <typename Comparable>
void BST<Comparable>::printMaxPath() const {
	if (root == nullptr) {
		std::cout << "Empty tree" << std::endl;
		return;
	}

	printMaxPath(root);
	std::cout << " </s>" << std::endl;
}

#endif

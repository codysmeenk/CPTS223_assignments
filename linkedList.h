#include <iostream>
#include <string>

using namespace std;

// Template class: the node in the linked list
template <typename T1, typename T2>
class Node {

public: 
	Node(T1 newCommand, T2 newDescription);

	Node(const Node<T1, T2>& copy);

	~Node();

	// getters
	T1 getCommand() const;
	T2 getDescription() const;

	Node* getNextPtr() const;

	// setters
	void setCommand(const T1 newCommand);
	void setDescription(const T2 newDescription);

	void setNextPtr(Node* const pNewNext);

private:

	T1 mCommand;
	T2 mDescription;

	Node* mpNext;

};

// Define the linked list class
template <typename T1, typename T2>
class LinkedList {

public:

	LinkedList();

	LinkedList(const LinkedList<T1, T2>& copy);

	~LinkedList();

	LinkedList<T1, T2>& operator=(const LinkedList<T1, T2>& rhs);

	Node<T1, T2>* getHeadPtr() const;

	void setHeadPtr(Node<T1, T2>* const pNewHead);

	bool insertAtFront(const T1& newCommand, const T2& newDescription);

	bool removeNode(const T1& removeCommand);

	int getSize() const;

	Node<T1, T2>* getNodeAt(int index) const;

private:

	Node<T1, T2>* mpHead;
	
};

template<typename T1, typename T2>
inline Node<T1, T2>::Node(T1 newCommand, T2 newDescription)
{
	mCommand = newCommand;
	mDescription = newDescription;
}

template<typename T1, typename T2>
inline Node<T1, T2>::Node(const Node<T1, T2>& copy)
{
	mCommand = copy.mCommand;
	mDescription = copy.mDescription;

	mpNext = copy.mpNext;
}

template<typename T1, typename T2>
inline Node<T1, T2>::~Node()
{
	//cout << "Inside Node's destructor!" << endl;
}

template<typename T1, typename T2>
inline T1 Node<T1, T2>::getCommand() const
{
	return mCommand;
}

template<typename T1, typename T2>
inline T2 Node<T1, T2>::getDescription() const
{
	return mDescription;
}

template<typename T1, typename T2>
Node<T1, T2>* Node<T1, T2>::getNextPtr() const
{
	return mpNext;
}

template<typename T1, typename T2>
inline void Node<T1, T2>::setCommand(const T1 newCommand)
{
	mCommand = newCommand;
}

template<typename T1, typename T2>
inline void Node<T1, T2>::setDescription(const T2 newDescription)
{
	mDescription = newDescription;
}

template<typename T1, typename T2>
void Node<T1, T2>::setNextPtr(Node<T1, T2>* const pNewNext)
{
	mpNext = pNewNext;
}

template<typename T1, typename T2>
inline LinkedList<T1, T2>::LinkedList()
{
	mpHead = nullptr;
}

template<typename T1, typename T2>
inline LinkedList<T1, T2>::LinkedList(const LinkedList<T1, T2>& copy)
{
	Node<T1, T2>* pCur = copy.mpHead;
	Node<T1, T2>* pCurNew = nullptr;
	mpHead = nullptr;

	if (copy.mpHead != nullptr)
	{
		mpHead = new Node<T1, T2>(pCur->getCommand(), pCur->getDescription());

		pCur = pCur->getNextPtr();
		pCurNew = mpHead;

		while (pCur != nullptr)
		{
			pCurNew->setNextPtr(new Node<T1, T2>(pCur->getCommand(), pCur->getDescription()));
			pCurNew = pCurNew->getNextPtr();
			pCur = pCur->getNextPtr();
		}
	}
}

template<typename T1, typename T2>
inline LinkedList<T1, T2>::~LinkedList()
{
	//cout << "Inside LinkedList's destructor!" << endl;

	Node<T1, T2>* pCur = mpHead;
	Node<T1, T2>* pNext = nullptr;

	while (pCur != nullptr)
	{
		pNext = pCur->getNextPtr();
		delete pCur;
		pCur = pNext;
	}

	mpHead = nullptr;
}

template<typename T1, typename T2>
inline LinkedList<T1, T2>& LinkedList<T1, T2>::operator=(const LinkedList<T1, T2>& rhs)
{
	if (this != &rhs)
	{
		Node<T1, T2>* pCur = mpHead;
		Node<T1, T2>* pNext = nullptr;

		while (pCur != nullptr)
		{
			pNext = pCur->getNextPtr();
			delete pCur;
			pCur = pNext;
		}

		mpHead = nullptr;

		if (rhs.mpHead != nullptr)
		{
			mpHead = new Node<T1, T2>(rhs.mpHead->getCommand(), rhs.mpHead->getDescription());

			pCur = rhs.mpHead->getNextPtr();
			Node<T1, T2>* pCurNew = mpHead;

			while (pCur != nullptr)
			{
				pCurNew->setNextPtr(new Node<T1, T2>(pCur->getCommand(), pCur->getDescription()));
				pCurNew = pCurNew->getNextPtr();
				pCur = pCur->getNextPtr();
			}
		}
	}

	return *this;
}

template<typename T1, typename T2>
inline Node<T1, T2>* LinkedList<T1, T2>::getHeadPtr() const
{
	return mpHead;
}

template<typename T1, typename T2>
inline void LinkedList<T1, T2>::setHeadPtr(Node<T1, T2>* const pNewHead)
{
	mpHead = pNewHead;
}

template<typename T1, typename T2>
inline bool LinkedList<T1, T2>::insertAtFront(const T1& newCommand, const T2& newDescription)
{
	Node<T1, T2>* pMem = new Node<T1, T2>(newCommand, newDescription);
	bool success = false;

	if (pMem != nullptr)
	{
		success = true;

		pMem->setNextPtr(mpHead);
		mpHead = pMem;
	}

	return success;
}

template<typename T1, typename T2>
inline bool LinkedList<T1, T2>::removeNode(const T1& removeCommand)
{
	Node<T1, T2>* pCur = mpHead;
	Node<T1, T2>* pPrev = nullptr;
	bool success = false;

	while (pCur != nullptr && pCur->getCommand() != removeCommand)
	{
		pPrev = pCur;
		pCur = pCur->getNextPtr();
	}

	if (pCur != nullptr)
	{
		success = true;

		if (pPrev == nullptr)
		{
			mpHead = pCur->getNextPtr();
		}
		else
		{
			pPrev->setNextPtr(pCur->getNextPtr());
		}

		delete pCur;
	}

	return success;
}

template<typename T1, typename T2>
inline int LinkedList<T1, T2>::getSize() const
{
	int count = 0;

	Node<T1, T2>* pCur = mpHead;

	while (pCur != nullptr)
	{
		count++;

		pCur = pCur->getNextPtr();
	}

	return count;
}

template<typename T1, typename T2>
inline Node<T1, T2>* LinkedList<T1, T2>::getNodeAt(int index) const
{
	if (index < 0)
	{
		return nullptr;
	}

	Node<T1, T2>* pCur = mpHead;

	int curIndex = 0;

	while (pCur != nullptr && curIndex < index)
	{
		pCur = pCur->getNextPtr();
		curIndex++;
	}

	return pCur;
}

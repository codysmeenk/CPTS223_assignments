#include <iostream>
#include <string>

using namespace std;

template <typename T1, typename T2>
class ArrayNode {

public:
	ArrayNode();

	ArrayNode(T1 newName, T2 newPoints);

	T1 getName() const;
	T2 getPoints() const;

	void setName(T1 newName);
	void setPoints(T2 newPoints);

private:

	T1 mName;
	T2 mPoints;

};


template <typename T1, typename T2>
class Array {

public:
	Array();

	Array(const Array<T1, T2>& copy);

	~Array();

	Array<T1, T2>& operator=(const Array <T1, T2>& rhs);

	ArrayNode<T1, T2>* getNodeAt(int index) const;

	int getSize() const;

	void insertInArray(T1 newName, T2 newPoints);

private:

	ArrayNode<T1, T2>** mArray;

	int mSize;
	int mCapacity;

	void resizeArray();
};

template<typename T1, typename T2>
inline ArrayNode<T1, T2>::ArrayNode()
{
	mName = T1();
	mPoints = T2();
}

template<typename T1, typename T2>
inline ArrayNode<T1, T2>::ArrayNode(T1 newName, T2 newPoints)
{
	mName = newName;
	mPoints = newPoints;
}

template<typename T1, typename T2>
inline T1 ArrayNode<T1, T2>::getName() const
{
	return mName;
}

template<typename T1, typename T2>
inline T2 ArrayNode<T1, T2>::getPoints() const
{
	return mPoints;
}

template<typename T1, typename T2>
inline void ArrayNode<T1, T2>::setName(T1 newName)
{
	mName = newName;
}

template<typename T1, typename T2>
inline void ArrayNode<T1, T2>::setPoints(T2 newPoints)
{
	mPoints = newPoints;
}

template<typename T1, typename T2>
inline Array<T1, T2>::Array()
{
	mSize = 0, mCapacity = 5;

	mArray = new ArrayNode<T1, T2>* [mCapacity];

	for (int i = 0; i < mCapacity; i++)
	{
		mArray[i] = nullptr;
	}
}

template<typename T1, typename T2>
inline Array<T1, T2>::Array(const Array<T1, T2>& copy)
{
	mSize = copy.mSize;
	mCapacity = copy.mCapacity;

	mArray = new ArrayNode<T1, T2>* [mCapacity];

	for (int i = 0; i < mSize; i++)
	{
		mArray[i] = new ArrayNode<T1, T2>(*copy.mArray[i]);
	}
}

template<typename T1, typename T2>
inline Array<T1, T2>::~Array()
{
	for (int i = 0; i < mSize; i++)
	{
		delete mArray[i];
	}

	delete[] mArray;
}

template<typename T1, typename T2>
inline Array<T1, T2>& Array<T1, T2>::operator=(const Array<T1, T2>& rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < mSize; i++)
		{
			delete mArray[i];
		}

		delete[] mArray;

		mSize = rhs.mSize;
		mCapacity = rhs.mCapacity;

		mArray = new ArrayNode<T1, T2>* [mCapacity];

		for (int i = 0; i < mSize; i++)
		{
			mArray[i] = new ArrayNode<T1, T2>(*rhs.mArray[i]);
		}
	}

	return *this;
}

template<typename T1, typename T2>
inline ArrayNode<T1, T2>* Array<T1, T2>::getNodeAt(int index) const
{
	if (index < 0 || index >= mSize)
	{
		return nullptr;
	}

	return mArray[index];
}

template<typename T1, typename T2>
inline int Array<T1, T2>::getSize() const
{
	return mSize;
}

template<typename T1, typename T2>
inline void Array<T1, T2>::insertInArray(T1 newName, T2 newPoints)
{
	if (mSize >= mCapacity)
	{
		resizeArray();
	}

	mArray[mSize] = new ArrayNode<T1, T2>(newName, newPoints);
	++mSize;
}

template<typename T1, typename T2>
inline void Array<T1, T2>::resizeArray()
{
	mCapacity = mCapacity * 2;

	ArrayNode<T1, T2>** newArray = new ArrayNode<T1, T2>* [mCapacity];

	for (int i = 0; i < mSize; i++)
	{
		newArray[i] = mArray[i];
	}

	delete[] mArray;

	mArray = newArray;
}


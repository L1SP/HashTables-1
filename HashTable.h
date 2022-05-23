#pragma once
#include <iostream>
using namespace std;
template <class TValue, class TKey>
class HashTable
{
public:
	virtual void print() = 0;
	virtual void insert(TKey key, TValue value) = 0;
	virtual bool remove(TKey key) = 0;
	virtual bool find(TKey key) = 0;
	virtual void clear() = 0;
	virtual bool isEmpty() = 0;
	virtual size_t Size() = 0;
};


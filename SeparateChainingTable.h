#pragma once
#include "HashTable.h"
#include <iostream>
#include <fstream>
using namespace std;
template <class TValue, class TKey>
class SeparateChainingTable : public HashTable<TValue, TKey>
{
	struct Node {
		TKey key;
		TValue value;
		Node* next;
		Node() : key(0), value("undefined"), next(0) {};
	};
	size_t capacity;
	size_t cellsCnt;
	size_t size;
	Node** cells;
	size_t Hash(TKey key);
public:
	SeparateChainingTable(size_t tableCapacity);
	SeparateChainingTable(const SeparateChainingTable& table);
	~SeparateChainingTable();
	void print();
	void insert(TKey key, TValue value);
	bool remove(TKey key);
	bool find(TKey key);
	void clear();
	//TValue get(TKey key);
	bool isEmpty();
	size_t Size();
	size_t Capacity();
	void Resize();
	void readFromFile(ifstream& ifs);
};
#include "SeparateChainingTable.inl"


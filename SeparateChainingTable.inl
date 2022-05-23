#include <iostream>
#include <fstream>
#include "File.h"
#include "Helper.h"
#include "SeparateChainingTable.h"
using namespace std;
/*size_t SeparateChainingTable<class TValue, class TKey>::Hash(TKey key) {
	size_t precision = 2;
	return ((size_t)key) >> precision;
}*/
template <class TValue, class TKey>
size_t SeparateChainingTable<TValue, TKey>::Hash(TKey key) {
	return key % capacity;
}
template <class TValue, class TKey>
SeparateChainingTable<TValue, TKey>::SeparateChainingTable(size_t tableCapacity) {
	capacity = tableCapacity;
	size = 0;
	cellsCnt = 0;
	cells = new Node* [capacity];
	for (size_t i = 0; i < capacity; ++i) {
		cells[i] = nullptr;
	}
}
template <class TValue, class TKey>
SeparateChainingTable<TValue, TKey>::SeparateChainingTable(const SeparateChainingTable& table) {
	capacity = table.capacity;
	size = table.size;
	cellsCnt = table.cellsCnt;
	cells = new Node* [capacity];
	for (size_t i = 0; i < capacity; ++i) {
		cells[i] = nullptr;
		if (table.cells[i]) {
			Node* p = table.cells[i];
			cells[i] = new Node;
			Node* q=cells[i];
			while (p) {
				q->value = p->value;
				q->key = p->key;
				q->next = new Node;
				q = q->next;
				p = p->next;
			}
		}
	}
}
template <class TValue, class TKey>
SeparateChainingTable<TValue, TKey>::~SeparateChainingTable() {
	clear();
	delete[] cells; 
}
template <class TValue, class TKey>
void SeparateChainingTable<TValue, TKey>::print() {
	for (size_t i = 0; i < capacity; ++i) {
		Node* p = cells[i];
		cout << "Index: " << i << ":\n";
		if (!p) {
			cout << "cell is empty";
		}
		while (p) {
			cout << "Value: " << p->value;
			cout << ", Key: "<<p->key<<'.';
			if (p->next)
				cout << '\n';
			p = p->next;
		}
		cout << '\n';
	}
}
template <class TValue, class TKey>
void SeparateChainingTable<TValue, TKey>::insert(TKey key, TValue value) {
	if (cellsCnt && (size + 1)/cellsCnt>10)
		Resize();
	size_t index = Hash(key);
	if (!cells[index])
		++cellsCnt;
	Node* node = new Node;
	node->key = key;
	node->value = value;
	node->next = cells[index];
	cells[index] = node;
	size++;
}
template <class TValue, class TKey>
bool SeparateChainingTable<TValue, TKey>::remove(TKey key) {
	size_t index = Hash(key);
	bool deleted = 0;
	if (cells[index]) {
		Node* p = cells[index];
		while (p && p->key == key) {
			Node* q = p;
			size--;
			cells[index] = p->next;
			p = p->next;
			delete q;
			deleted = 1;
		}
		while (p) {
			if (p->next && key == p->next->key) {
				size--;
				Node* q = p->next;
				p->next = q->next;
				delete q;
				p = p->next;
				deleted = 1;
			}
		}
		if (!cells[index])
			cellsCnt--;
	}
	return deleted;
}
template <class TValue, class TKey>
bool SeparateChainingTable<TValue, TKey>::find(TKey key) {
	size_t index = Hash(key);
	if (cells[index]){
		Node* p = cells[index];
		while (p) {
			if (key == p->key)
				return 1;
			p = p->next;
		}
	}
	return 0;
}
template <class TValue, class TKey>
void SeparateChainingTable<TValue, TKey>::clear() {
	for (size_t i = 0; i < capacity; ++i) {
		Node* p = cells[i];
		while (p) {
			Node* q = p;
			p = p->next;
			delete q;
		}
		cells[i] = nullptr;
	}
	size = 0;
	cellsCnt = 0;
}
/*template <class TValue, class TKey>
TValue SeparateChainingTable<TValue, TKey>::get(TKey key) {
	size_t index = Hash(key);
	if (cells[index]){
		Node* p = cells[index];
		while (p) {
			if (key == p->key)
				return p->value;
		}
	}
	return "undefined";
}*/
template <class TValue, class TKey>
bool SeparateChainingTable<TValue, TKey>::isEmpty() {
	for (size_t i = 0; i < capacity; ++i) {
		if (cells[i])
			return 0;
	}
	return 1;
}
template <class TValue, class TKey>
size_t SeparateChainingTable<TValue, TKey>::Size() {
	return size;
}
template <class TValue, class TKey>
size_t SeparateChainingTable<TValue, TKey>::Capacity() {
	return capacity;
}
template <class TValue, class TKey>
void SeparateChainingTable<TValue, TKey>::Resize() {
	SeparateChainingTable<TValue, TKey> newTable(nearestPrime(capacity*2));
	for (size_t i = 0; i < capacity; ++i) {
		Node* p = cells[i];
		while (p) {
			newTable.insert(p->key, p->value);
			Node* q = p;
			p = p->next;
			delete q;
			q = nullptr;
		}
		delete cells[i];
		cells[i] = nullptr;
	}
	delete[]cells;
	cells = newTable.cells;
}
template <class TValue, class TKey>
void SeparateChainingTable<TValue, TKey>::readFromFile(ifstream& ifs) {
	bool firstFile = 1;
	while (!ifs.eof()) {
		File f;
		string tempString;
		if (!firstFile)
			getline(ifs, tempString); // пустая строка:)
		else if (firstFile)
			firstFile = 0;
		getline(ifs, f.cat);
		getline(ifs, f.name);
		getline(ifs, f.ext);
		getline(ifs, tempString);
		f.date.day = stoi(tempString);
		getline(ifs, tempString);
		f.date.month = stoi(tempString);
		getline(ifs, tempString);
		f.date.year = stoi(tempString);
		getline(ifs, tempString);
		f.size = stoi(tempString);
		insert(f.getKey(capacity), f.getValue());
	}
}

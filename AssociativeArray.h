//Programmer: Jaewon Lee
//Programmer's ID: 1725935

#ifndef ASSOCIATIVEARRAY_LABEXCERCISE8_H
#define ASSOCIATIVEARRAY_LABEXCERCISE8_H

#include "Queue.h"

template <typename K, typename V>
class AssociativeArray {
	struct Node {
		K key;
		V value;
		Node* next;
	};

	Node* firstNode;
	int siz;

public:
	AssociativeArray() { firstNode = 0; siz = 0; }
	AssociativeArray(const AssociativeArray<K, V>&);
	AssociativeArray<K, V>& operator=(const AssociativeArray<K, V>&);
	~AssociativeArray();
	V operator[](const K&) const;
	V& operator[](const K&);
	bool containKey(const K&) const; // for just cheking include the key or not
	void deleteKey(const K&);
	Queue<K> keys(); // return all valid keys
	int size() const;
	void clear();
};

template<typename K, typename V>
AssociativeArray<K, V>::AssociativeArray(const AssociativeArray<K, V>& original) {
	firstNode = 0;
	Node* lastNode = 0;
	siz = original.siz;

	for (Node* p = original.firstNode; p; p = p->next) {
		Node* temp = new Node{ p->key, p->value, 0 };
		if (lastNode) lastNode->next = temp;
		else firstNode = temp;
		lastNode = temp;
	}
}

template<typename K, typename V>
AssociativeArray<K, V>& AssociativeArray<K, V>::operator=(const AssociativeArray<K, V>& original){
	if (this != &original) {
		while (firstNode) {
			Node* p = firstNode;
			firstNode = firstNode->next;
			delete p;
		}

		Node* lastNode = 0;
		siz = original.siz;
		for (Node* p = original.firstNode; p; p = p->next) {
			Node* temp = new Node{ p->key, p->value, 0 };

			if (lastNode) lastNode->next = temp;
			else firstNode = temp;
			lastNode = temp;
		}
	}
	return *this;
}

template<typename K, typename V>
AssociativeArray<K, V>::~AssociativeArray() {
	if (firstNode != 0) {
		while (firstNode) {
			Node* temp = firstNode;
			firstNode = firstNode->next;
			delete temp;
		}
	}
	siz = 0;
}

template<typename K, typename V>
V AssociativeArray<K, V>::operator[](const K& key) const {
	for(Node* scan = firstNode; scan; scan= scan->next)
		if (scan->key = key) return scan->value;
	return V(); // if return type is "const V&", return dummy
}

template<typename K, typename V>
V& AssociativeArray<K, V>::operator[](const K& key) {
	for (Node* scan = firstNode; scan; scan = scan->next)
		if (scan->key == key) 
			return scan->value;

	Node* temp = new Node{ key, V(), firstNode };
	firstNode = temp;
	siz++;
	return firstNode->value;
}

template<typename K, typename V>
bool AssociativeArray<K, V>::containKey(const K& key) const {
	for (Node* scan = firstNode; scan; scan = scan->next)
		if (scan->key == key) return true;
	return false;
}

template<typename K, typename V>
void AssociativeArray<K, V>::deleteKey(const K& key) {
	Node* p;
	Node* prev;
	for (p = firstNode, prev = 0; p; prev = p, p = p->next)
		if (p->key == key)
			break;
	if (p) {
		siz--;
		if (prev) prev->next = p->next;
		else firstNode = p->next;
		delete p;
	}
}

template<typename K, typename V>
Queue<K> AssociativeArray<K, V>::keys() {
	Queue<K> listOfKey;
	for (Node* scan = firstNode; scan; scan = scan->next)
		listOfKey.push(scan->key);
	return listOfKey;
}

template<typename K, typename V>
int AssociativeArray<K, V>::size() const {
	return siz;
}

template<typename K, typename V>
void AssociativeArray<K, V>::clear() {
	if (firstNode != 0) {
		while (firstNode) {
			Node* temp = firstNode;
			firstNode = firstNode->next;
			delete temp;
		}
	}
	siz = 0;
}



#endif // !ASSOCIATIVEARRAY_LABEXCERCISE8_H

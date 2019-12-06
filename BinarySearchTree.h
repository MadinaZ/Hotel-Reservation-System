//Programmer: Hiroaki Takeuchi
//Programmer's ID: 1718699

#ifndef BinarySearchTree_h
#define BinarySearchTree_h

#include <queue>
using namespace std;

template<typename K, typename V>
class BinarySearchTree
{
	struct Node
	{
		K key;
		V value;
		Node* left;
		Node* right;
	};

	Node* rootNode;
	int siz;
	void keys(const Node*, queue<K>&) const;
	void clear(Node*);
	void copyTree(Node*, const Node*);

public:
	BinarySearchTree() { rootNode = 0; siz = 0; }
	BinarySearchTree(const BinarySearchTree&);
	BinarySearchTree<K, V>& operator=(const BinarySearchTree<K, V>&);
	~BinarySearchTree() { clear(rootNode); }

	int size() const { return siz; }
	V operator[] (const K&) const;
	V& operator[] (const K&);
	bool containsKey(const K&) const;
	void deleteKey(const K&);
	queue<K> Keys() const;
	void clear();
};



template<typename K, typename V>
BinarySearchTree<K,V>::BinarySearchTree(const BinarySearchTree& original)
{
	if (rootNode == original.rootNode) return *this;
	rootNode = 0;
	if (original.rootNode) copyTree(rootNode = new Node, original.rootNode);
	siz = original.siz;
}

template<typename K, typename V>
BinarySearchTree<K,V>& BinarySearchTree<K,V>::operator=(const BinarySearchTree<K, V>& original)
{
	if(this == &original) return *this;

	if (rootNode == original.rootNode) return *this;
	rootNode = 0;
	if (original.rootNode) copyTree(rootNode = new Node, original.rootNode);
	siz = original.siz;

	return *this;
}

template<typename K, typename V>
void BinarySearchTree<K,V>::keys(const Node* p, queue<K>& q) const
{
	if (!p) return;
	keys(p->left, q);
	q.push(p->key);
	keys(p->right, q);
}

template<typename K, typename V>
void BinarySearchTree<K,V>::clear(Node* p)
{
	if (!p) return;
	clear(p->left);
	clear(p->right);
	delete p;
}

template<typename K, typename V>
void BinarySearchTree<K,V>::copyTree(Node* p, const Node* copiedTree)
{
	if (!p) return;
	p->key = copiedTree->key;
	p->value = copiedTree->value;
	p->left = p->right = 0;
	if (copiedTree->left) copyTree(p->left = new Node, copiedTree->left);
	if (copiedTree->right) copyTree(p->right = new Node, copiedTree->right);
}


template<typename K, typename V>
V BinarySearchTree<K,V>::operator[](const K& key) const
{
	Node* p = rootNode;
	while (p)
	{
		if (p->key == key) break;
		if (p->key < key) p = p->right; else p = p->left;
	}

	if (p) return p->value;
	return V();
}

template<typename K, typename V>
V& BinarySearchTree<K,V>::operator[](const K& key)
{
	Node* p = rootNode;
	Node* prev = 0;

	if (p == 0)
	{
		siz++;
		rootNode = new Node;
		rootNode->key = key;
		rootNode->value = V();
		rootNode->left = rootNode->right = 0;
		return rootNode->value;
	}

	while (p)
	{
		if (p->key == key) break;
		prev = p;
		if (p->key < key) p = p->right; else p = p->left;
	}

	if(p != 0)	return p->value;

	siz++;
	p = new Node; // p = new Node{key, V()}; C++11
	p->key = key;
	p->value = V();
	p->left = p->right = 0;

	if (prev->key < key) prev->right = p;
	else prev->left = p;
	return p->value;
}

template<typename K, typename V>
bool BinarySearchTree<K,V>::containsKey(const K& key) const
{
	Node* p = rootNode;
	while (p)
	{
		if (p->key == key) break;
		if (p->key < key) p = p->right; else p = p->left;
	}

	return p != 0;
}

template<typename K, typename V>
void BinarySearchTree<K,V>::deleteKey(const K& key)
{
	Node* p = rootNode;
	Node* prev = 0;

	if (p == 0) return;
	while (p)
	{
		if (p->key == key) break;
		prev = p;
		if (p->key < key) p = p->right; else p = p->left;
	}

	if (p->left == 0 && p->right == 0 && prev == 0)
	{
		delete p;
		rootNode = 0;
		siz--;
		return;
	}
	else if (p->left == 0 && p->right == 0 && prev != 0) // no descendet
	{
		if (prev->left == p) prev->left = 0;
		else prev->right = 0;
		delete p;
		siz--;
		return;
	}
	else if (p->left == 0 && p->right != 0 && prev != 0)  //right descendent
	{
		if (prev->left == p) prev->left = p->right;
		else prev->right = p->right;
		delete p;
		siz--;
		return;
	}
	else if (p->left != 0 && p->right == 0)  // left descendent
	{
		if (prev->left == p) prev->left = p->left;
		else prev->right = p->left;
		delete p;
		siz--;
		return;
	}
	//both decsindet
	Node* pSave = p;
	prev = p;
	p = p->left;

	while (p->left != 0)
	{
		prev = p;
		p = p->left;
	}

	pSave->key = p->key;
	pSave->value = p->value;
	if (prev->left == p) prev->left = p->right;
	else prev->right = p->right;
	delete p;
	siz--;

}

template<typename K, typename V>
queue<K> BinarySearchTree<K,V>::Keys() const
{
	queue<K> result;
	keys(rootNode, result);
	return result;
}

template<typename K, typename V>
void BinarySearchTree<K,V>::clear()
{
	clear(rootNode);
	rootNode = 0;
	siz = 0;
}

#endif

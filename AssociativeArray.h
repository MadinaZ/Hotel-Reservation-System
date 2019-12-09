#ifndef AssociativeArray_h
#define AssociativeArray_h

#include "safedelete.h"

#include <queue>
using namespace std;



/////////
template<typename K, typename V>
class AssociativeArray
{
  struct Node
  {
    Node():key(),value(),inUse(false){}

    void copy(const Node& node)
    {
      this->key = node.key;
      this->value = node.value;
      this->inUse = node.inUse;
    }

    K key;
    V value;
    bool inUse;
  };
  
  Node* data;
  int siz = 0;
  int cap;
  void capacity(int);
  
public:
  AssociativeArray(int = 2);
  AssociativeArray(const AssociativeArray<K,V>&);
  AssociativeArray<K,V>& operator=(const AssociativeArray<K,V>&);
  ~AssociativeArray() { safedeleteArray(data); }
  V operator[](const K&) const;
  V& operator[](const K&);
  bool containsKey(const K&) const;
  void deleteKey(const K&);
  queue<K> keys() const;
  int size() const { return siz; }
  void clear();
};

template<typename K, typename V>
void AssociativeArray<K,V>::capacity(int cap)
{
  if(this->cap == cap) { return; }
  
  Node* temp = new Node[cap];
  int limit = (cap < this->cap ? cap : this->cap);
  for(int i = 0; i < limit; i++)
    temp[i].copy(data[i]);
  safedeleteArray(data);
  data = temp;
  this->cap = cap;
}

template<typename K, typename V>
AssociativeArray<K,V>::AssociativeArray(int cap)
:data(new Node[cap])
,siz(0)
,cap(cap)
{}

template<typename K, typename V>
AssociativeArray<K,V>::AssociativeArray(const AssociativeArray<K,V>& original)
:data(new Node[original.cap])
,siz(original.siz)
,cap(original.cap)
{
  for(int i = 0; i < cap; i++)
    data[i].copy(original.data[i]);
}

template<typename K, typename V>
AssociativeArray<K,V>& AssociativeArray<K,V>::operator=(const AssociativeArray<K,V>& original)
{
  if(this == &original) { return *this; }
  
  safedeleteArray(data);
  this->cap = original.cap;
  data = new Node[cap];
  for(int i = 0; i < cap; i++)
    data[i].copy(original.data[i]);
  
  return *this;
}

template<typename K, typename V>
V AssociativeArray<K,V>::operator[](const K& key) const
{
  for(int i = 0; i < cap; i++)
    if(data[i].inUse && data[i].key == key)
      return data[i].value;
  return V();
}

template<typename K, typename V>
V& AssociativeArray<K,V>::operator[](const K& key)
{
  int firstUnusedIndex = cap;
  for(int i = 0; i < cap; i++)
  {
    if(data[i].inUse)
    {
      if(data[i].key == key)
        return data[i].value;
    }
    else if(firstUnusedIndex == cap)
      firstUnusedIndex = i;
  }

  if(firstUnusedIndex == cap) capacity(cap * 2);
  data[firstUnusedIndex].key = key;
  data[firstUnusedIndex].value = V();
  data[firstUnusedIndex].inUse = true;
  siz++;
  return data[firstUnusedIndex].value;
}

template<typename K, typename V>
bool AssociativeArray<K,V>::containsKey(const K& key) const
{
  for(int i = 0; i < cap; i++)
    if(data[i].inUse && data[i].key == key)
      return true;
  return false;
}

template<typename K, typename V>
void AssociativeArray<K,V>::deleteKey(const K& key)
{
	for(int i = 0; i < cap; i++)
	{
		if(data[i].inUse && data[i].key == key)
		{
			data[i].inUse = false;
			siz--;
			return;
		}
	}
}

template<typename K, typename V>
queue<K> AssociativeArray<K,V>::keys() const
{
  queue<K> k_queue;
  for(int i = 0; i < cap; i++)
    if(data[i].inUse)
      k_queue.push(data[i].key);
  return k_queue;
}

template<typename K, typename V>
void AssociativeArray<K,V>::clear()
{
  for(int i = 0; i < cap; i++)
    data[i].inUse = false;
  siz = 0;
}

#endif 

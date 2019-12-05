//  Programmer: Hiroaki Takeuchi
//  Programmer's ID: 1718699
#include <algorithm>
using namespace std;

#ifndef PriorityQueue_h
#define PriorityQueue_h


template<typename T>
void safedeleteArray(T*& p)
{
	delete[] p;
	p = NULL;
}

template<typename V>
class PriorityQueue
{
	V* values;
	int cap;
	int siz;
	void capacity(int);

public:
	PriorityQueue(int =2);
	PriorityQueue(const PriorityQueue<V>&);
	~PriorityQueue() { safedeleteArray(values); }
	PriorityQueue<V>& operator=(const PriorityQueue<V>&);

	void push(const V&);
	void pop();
	V top() const { return siz == 0 ? V() : values[0]; }
	int size() const { return siz; }
	bool empty() const { return siz == 0 ? true : false; }
	void clear() {siz = 0; }
};

template<typename V>
void PriorityQueue<V>::capacity(int cap)
{
	if(this->cap == cap) return;

	V* temp = new V[cap];
	for(int i = 0; i < cap; i++)
		temp[i] = values[i];

	safedeleteArray(values);
	values = temp;
	this->cap = cap;
}

template<typename V>
PriorityQueue<V>::PriorityQueue(int cap)
:values(new V[cap])
,cap(cap)
,siz(0)
{};

template<typename V>
PriorityQueue<V>::PriorityQueue(const PriorityQueue<V>& original)
:values(new V[original.cap])
,cap(original.cap)
,siz(original.siz)
{
	for(int i = 0; i < cap; i++)
		values[i] = original.values[i];
};

template<typename V>
PriorityQueue<V>& PriorityQueue<V>:: operator=(const PriorityQueue<V>& original)
{
	if(this == &original) { return *this; }

	safedeleteArray(values);
	this->cap = original.cap;
	values = new V[cap];
	for(int i = 0; i < cap; i++)
		values[i] = original.values[i];

	return *this;
}

template<typename V>
void PriorityQueue<V>::push(const V& value)
{
	if(siz >= cap) capacity(cap*2);

	values[siz] = value;
	int index = siz;
	int p_index = (index + 1) / 2 - 1;
	++siz;

	while(p_index >= 0)
	{
		if(values[p_index] < values[index])
		{
			swap(values[index], values[p_index]);
			index = p_index;
			p_index = (index + 1) / 2 - 1;
		}
		else
			break;
	}
}

template<typename V>
void PriorityQueue<V>::pop()
{
	if(siz == 0) return;

	values[0] = values[--siz];
	int index = 0, big_index = 0;
	int l_index = index * 2 + 1; if(l_index > siz) return;
	int r_index = index * 2 + 2;

	while(true)
	{
		if(r_index > siz)
			big_index = l_index;
		else
		{
			if(values[r_index] < values[l_index])
				big_index = l_index;
			else
				big_index = r_index;
		}
		if(values[index] < values[big_index])
		{
			swap(values[big_index], values[index]);
			index = big_index;
			l_index = index * 2 + 1; if(l_index > siz) break;
			r_index = index *  2 + 2;
		}
		else
			break;
	}
}


#endif

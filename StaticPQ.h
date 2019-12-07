//  Programmer: Hiroaki Takeuchi
//  Programmer's ID: 1718699
#include "safedelete.h"

#include <algorithm>
using namespace std;

#ifndef StaticPQ_h
#define StaticPQ_h



template<typename V, int CAP>
class StaticPQ
{
	V* values;
	int siz;
	V dummy;


public:
	StaticPQ();
	StaticPQ<V, CAP>& operator=(const StaticPQ<V, CAP>&);
	const V& operator[](int) const; // cannot access elements in order , but OK
	V& operator[](int);						  // cannot access elements in order , but OK
	int index(int) const;
	int capacity() { return CAP; }
	void push(const V&);
	void pop();
	V top() const { return siz == 0 ? V() : values[0]; }
	int size() const { return siz; }
	bool empty() const { return siz == 0 ? true : false; }
	void clear() {siz = 0; }
};

template<typename V, int CAP>
StaticPQ<V, CAP>::StaticPQ()
:values(new V[CAP])
,siz(0)
,dummy(V())
{
	for(int i = 0; i < CAP; i++)
		values[i] = V();
};

template<typename V, int CAP>
StaticPQ<V, CAP>& StaticPQ<V,CAP>::operator=(const StaticPQ<V, CAP>& ori)
{
	if(this == &ori) return *this;

	safedeleteArray(values);
	for(int i = 0; i < CAP; i++)
		values[i] = ori.values[i];
	siz = ori.siz;
	dummy = ori.dummy;

	return *this;
}

template<typename V, int CAP>
const V& StaticPQ<V, CAP>:: operator[](int index) const
{
  if(index < 0 || index >= CAP) return dummy;
  else return values[index];
}

template<typename V, int CAP>
V& StaticPQ<V, CAP>:: operator[](int index)
{
	if(index < 0 || index >= CAP)
		return dummy;
	else
		return values[index];
}

template<typename V, int CAP>
void StaticPQ<V, CAP>::push(const V& value)
{
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

template<typename V, int CAP>
void StaticPQ<V, CAP>::pop()
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
//  Programmer: Hiroaki Takeuchi
//  Programmer's ID: 1718699
#include "safedelete.h"


#include <algorithm>
using namespace std;


#ifndef SortableArray_h
#define SortableArray_h


template<typename T>
class SortableArray
{
	T* values;
	T dummy = T();
	int cap;

public:
	SortableArray(int = 2);
	SortableArray(const SortableArray<T>&);// copy constructor
	~SortableArray() { safedeleteArray(values); }
	SortableArray<T>& operator=(const SortableArray<T>&);

	int capacity() const {return cap;}
	void capacity(int); //setter
	const T& operator[](int) const; //getter
	T& operator[](int); //setter

	void sort(int); // sort first int indexes (heap sort)
};

template<typename T>
SortableArray<T>::SortableArray(int cap)
:values(new T[cap])
,cap(cap)
{
	for(int i = 0; i < cap; i++)
		values[i] = T();
}

template<typename T>
SortableArray<T>::SortableArray(const SortableArray<T>& original)
:values(new T[original.cap])
,dummy(original.dummy)
,cap(original.cap)
{
	for(int i = 0; i < cap; i++)
		values[i] = original.values[i];
}

template<typename T>
void SortableArray<T>::capacity(int cap)
{
	T* temp = new T[cap];
	int limit = (cap < this->cap ? cap : this->cap);

	for(int i = 0; i < limit; i++)
		temp[i] = values[i];

	for(int i = limit; i < cap; i++)
		temp[i] = T();

	delete[] values;
	values = temp;
	this->cap = cap;
}

template<typename T>
SortableArray<T>& SortableArray<T>::operator=(const SortableArray<T>& original)
{
	if(this == &original) { return *this; }

	delete []values;
	cap = original.cap;
	values = new T[cap];
	for (int i = 0; i < cap; i++)
		values[i] = original.values[i];
	dummy = original.dummy;

	return *this;
}

template<typename T>
const T& SortableArray<T>::operator[](int index) const
{
	if(index < 0 || index >= cap) return dummy;
	else return values[index];
}

template<typename T>
T& SortableArray<T>::operator[](int index)
{
	if(index < 0)
		return dummy;
	if(index >=cap)
		capacity(index*2); //in case user input out of bound
	return values[index];
}

template<typename T>
void SortableArray<T>::sort(int num)
{
  for (int i = 1; i < num; i++)
  {
    for (int index = i;;)
    {
      int p_index = (index + 1) / 2 - 1;
      if (p_index < 0) break;
      if (values[p_index] >= values[index]) break;
      swap(values[p_index], values[index]);
      index = p_index;
    }
  }

  for (int index = num - 1; index > 0; index--)
  {
    swap(values[0], values[index]);
    int p_index = 0;
    while (true)
    {
      int l_index = 2 * p_index + 1;
      int r_index = 2 * p_index + 2;
      if (l_index >= index) break; // leaf at p_index
      if (r_index >= index) // one-child for p_index
      {
          if (values[l_index] <= values[p_index]) break;
          swap(values[l_index], values[p_index]);
          p_index = l_index;
      }
      else if (values[r_index] < values[l_index])
      {
        if (values[l_index] <= values[p_index]) break;
        swap(values[l_index], values[p_index]);
        p_index = l_index;
      }
      else
      {
        if (values[r_index] <= values[p_index]) break;
        swap(values[r_index], values[p_index]);
        p_index = r_index;
      }
    }
  }

}


#endif

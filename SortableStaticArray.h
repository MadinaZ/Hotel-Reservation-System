//  Programmer: Hiroaki Takeuchi
//  Programmer's ID: 1718699
#include <algorithm>
using namespace std;

#ifndef SortableStaticArray_h
#define SortableStaticArray_h

template<typename T, int CAP>
void safedeleteArray(T*& p)
{
	delete [] p;
	p = nullptr;
}

template<typename T, int CAP>
class SortableStaticArray
{
	T* values;
	T dummy = T();

public:
	SortableStaticArray();
	SortableStaticArray(const SortableStaticArray<T, CAP>&);// copy constructor
	~SortableStaticArray() { safedeleteArray(values); }
	SortableStaticArray<T, CAP>& operator=(const SortableStaticArray<T, CAP>&);

	int capacity() const {return CAP;}
	const T& operator[](int) const; //getter
	T& operator[](int); //setter

	void sort(int); // sort first int indexes (heap sort)
};

template<typename T, int CAP>
SortableStaticArray<T, CAP>::SortableStaticArray()
:values(new T[CAP])
{
	for(int i = 0; i < CAP; i++)
		values[i] = T();
}

template<typename T, int CAP>
SortableStaticArray<T, CAP>::SortableStaticArray(const SortableStaticArray<T, CAP>& original)
:values(new T[CAP])
,dummy(original.dummy)
{
	for(int i = 0; i < CAP; i++)
		values[i] = original.values[i];
}

template<typename T, int CAP>
SortableStaticArray<T, CAP>& SortableStaticArray<T, CAP>::operator=(const SortableStaticArray<T, CAP>& original)
{
	if(this == &original) { return *this; }

	delete []values;
	values = new T[CAP];
	for (int i = 0; i < CAP; i++)
		values[i] = original.values[i];
	dummy = original.dummy;

	return *this;
}

template<typename T, int CAP>
const T& SortableStaticArray<T, CAP>::operator[](int index) const
{
	if(index < 0 || index >= CAP) return dummy;
	else return values[index];
}

template<typename T, int CAP>
T& SortableStaticArray<T, CAP>::operator[](int index)
{
	if(index < 0 || index >= CAP)
		return dummy;

	return values[index];
}

template<typename T, int CAP>
void SortableStaticArray<T, CAP>::sort(int num)
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

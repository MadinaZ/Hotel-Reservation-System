#ifndef DynamicArray_h
#define DynamicArray_h


template<typename T>
class DynamicArray
{
	T* values;
	T dummy = T();
	int cap;

public:
	DynamicArray(int = 2);
	DynamicArray(const DynamicArray<T>&);// copy constructor
	~DynamicArray(){ safedeleteArray(values); }
	DynamicArray<T>& operator=(const DynamicArray<T>&);
	int capacity() const {return cap;}
	void capacity(int); //setter
	const T& operator[](int) const; //getter
	T& operator[](int); //setter
};

template<typename T>
DynamicArray<T>::DynamicArray(int cap)
:values(new T[cap])
,cap(cap)
{
	for(int i = 0; i < cap; i++)
		values[i] = T();
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& original)
:cap(original.cap)
,values(new T[cap])
,dummy(original.dummy)
{
	for(int i = 0; i < cap; i++)
		values[i] = original.values[i];
}

template<typename T>
void DynamicArray<T>::capacity(int cap)
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
DynamicArray<T>& DynamicArray<T>::operator =(const DynamicArray<T>& original)
{
	if(this == &original) { return; }

	delete []values;
	cap = original.cap;
	values = new T[cap];
	for (int i = 0; i < cap; i++)
		values[i] = original.values[i];
	dummy = original.dummy;

	return *this;
}

template<typename T>
const T& DynamicArray<T>::operator[](int index) const
{
	if(index < 0 || index >= cap) return dummy;
	else return values[index];
}

template<typename T>
T& DynamicArray<T>::operator[](int index)
{
	if(index < 0)
		return dummy;
	if(index >=cap)
		capacity(index*2); //in case user input out of bound
	return values[index];
}

#endif

#ifndef DynamicArray_h
#define DynamicArray_h


template<typename T>
class DynamicArray
{
	T* values;
	T dummy = T();
	int cap;
	int siz;
	void capacity(int); //setter

public:
	DynamicArray(int = 2);
	DynamicArray(const DynamicArray<T>&);// copy constructor
	~DynamicArray(){ safedeleteArray(values); }
	DynamicArray<T>& operator=(const DynamicArray<T>&);
	int size() const { return siz; }
	int capacity() const { return cap; }
	const T& operator[](int) const; //getter
	T& operator[](int); //setter
};

template<typename T>
DynamicArray<T>::DynamicArray(int cap)
:values(new T[cap])
,cap(cap)
,siz(0)
{
	for(int i = 0; i < cap; i++)
		values[i] = T();
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& original)
:cap(original.cap)
,values(new T[cap])
,dummy(original.dummy)
,siz(0)
{
	for(int i = 0; i < cap; i++)
	{
		values[i] = original.values[i];
		++siz;
	}
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

	int size = siz;
	safeDeleteArray(values);
	values = temp;
	this->cap = cap;
	this->siz = size;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& original)
{
	if(this == &original) { return; }

	delete []values;
	cap = original.cap;
	values = new T[cap];
	for (int i = 0; i < cap; i++)
		values[i] = original.values[i];
	dummy = original.dummy;
	siz = original.siz;

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
	++siz;
	return values[index];
}

#endif

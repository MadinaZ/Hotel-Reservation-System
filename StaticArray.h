#ifndef StaticArray_h
#define StaticArray_h



template<typename T, int CAP>
class StaticArray
{
	T values[CAP];
	T dummy;

public:
	StaticArray();
	int capacity() const {return CAP;}
	const T& operator[](int) const; //getter
	T& operator[](int); //setter
};

template<typename T, int CAP>
StaticArray<T, CAP>::StaticArray()
{
	for(int i = 0; i < CAP; i++)
		values[i] = T();

	dummy = T();
}

template<typename T, int CAP>
const T& StaticArray<T, CAP>::operator[](int index) const
{
	if(index < 0 || index >= CAP) return dummy;
	else return values[index];
}

template<typename T, int CAP>
T& StaticArray<T, CAP>::operator[](int index)
{
	if(index < 0 || index >= CAP)
		return dummy;
	else
		return values[index];
}

#endif

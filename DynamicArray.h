//
//  DynamicArray.h
//  lab_5.1
//
//  Created by Madina on 9/25/19.
//  Copyright © 2019 Madina. All rights reserved.

#ifndef DynamicArray_h
#define DynamicArray_h

template<typename T>
class DynamicArray
{
    T* value;
    int cap;
    T dummy = T();
public:
    DynamicArray(int = 2);
    DynamicArray(const DynamicArray<T>&);
    ~DynamicArray(){delete [ ] value;}
    DynamicArray<T>& operator = (const DynamicArray<T>&);
    int capacity() const;
    void capacity(int);
    T operator[ ] (int) const;
    T& operator[ ] (int);
};

template<typename T>
DynamicArray<T>::DynamicArray(int cap)
{
    this->cap = cap;
    value = new T[cap];
    
    for(int i = 0; i < cap; i++)
        value[i] = T();
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& original)
{
    cap = original.cap;
    value = new T[cap];
    
    for(int i = 0; i < cap; i++)
        value[i] = original.value[i];
    dummy = original.dummy;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& original)
{
    if(this != &original)
    {
        delete [ ] value;
        
        cap = original.cap;
        value = new T[cap];
        for(int i = 0; i < cap; i++)
            value[i] = original.value[i];
        dummy = original.dummy;
    }
    return *this; //to match the data type
}

template<typename T>
int DynamicArray<T>:: capacity() const
{
    return cap;
}

template<typename T>
void DynamicArray<T>:: capacity(int cap)
{
    T* temp = new T[cap];
    for(int i = 0; i < this->cap; i++)
        temp[i] = value[i];
    
    for(int i = this->cap; i < cap; i++)
        temp[i] = T();
    delete [ ] value;
    value = temp;
    this->cap = cap; //reassign our capacity to the newly created one.
}

template<typename T>
T DynamicArray<T>::operator[](int index) const
{
    if(index < 0)
        return dummy;
    if(index >= cap)
        return dummy;
    else
        return value[index];
}

template<typename T>
T& DynamicArray<T>:: operator[ ] (int index)
{
    if(index < 0)
        return dummy;
    if(index >= cap)
        capacity(index*2);
        return value[index];
}

#endif /* DynamicArray_h */

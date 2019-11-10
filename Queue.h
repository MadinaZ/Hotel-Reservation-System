//
//  Queue.h
//  Lab-6-2
//
//  Created by Madina Sadirmekova on 10/14/19.
//  Copyright © 2019 Madina Sadirmekova. All rights reserved.
//
#ifndef Queue_h
#define Queue_h

template<typename V>
class Queue
{
    struct Node
    {
        V value;
        Node* next;
    };
    
    Node* firstNode;
    Node* lastNode;
    int siz;
    V dummy = V();
    
public:
    Queue();
    Queue(const Queue<V>&); //copy constructor
    Queue<V>& operator = (const Queue<V>&);
    ~Queue();
    void push(const V&);
    const V& front() const;
    const V& back() const;
    
    void pop();
    void clear();
    int size() const;
    bool empty() const;
};

template<typename V>
Queue<V>::Queue()
{
    firstNode = 0;
    lastNode = 0;
    siz = 0;
};

template<typename V>
Queue<V>::Queue(const Queue<V>& original)//copy
{
    this->firstNode = 0;
    this->lastNode = 0;
    siz = original.siz;
    for(Node* p = original.firstNode; p; p = p->next)
    {
        Node* temp = new Node{p->value,0};
//        temp->value = p->value;
//        temp->next = 0;
        if(lastNode)
            lastNode->next = temp;
        else
            firstNode = temp;
        lastNode = temp;
    }
}

template<typename V>
Queue<V>::~Queue()
{
    while(firstNode)
    {
        Node* p = firstNode;
        firstNode = firstNode->next;
        delete p;
        siz--;
    }
}

template<typename V>
Queue<V>& Queue<V>::operator=(const Queue<V>& original)//assign
{
    if(this != &original)
    {
        while(firstNode)
        {
            Node *p = firstNode;
            firstNode = firstNode->next;
            delete p;
        }
        
        this->lastNode = 0;
        for(Node* p = original.firstNode; p; p = p->next)
        {
            Node* temp = new Node{p->value,0};
//            temp->value = p->value;
//            temp->next = 0;
            if(lastNode)
                lastNode->next = temp;
            else
                firstNode = temp;
            lastNode = temp;
        }
        siz = original.siz;
    }
    return *this; //to match the data type
}

template<typename V>
void Queue<V>::push(const V& value)
{
    Node* temp = new Node{value,0};
    if(lastNode)//whenever my lastNode points to somehwere
        lastNode->next = temp;
    else
        firstNode = temp;
    lastNode = temp;
    ++siz;
}

template<typename V>
const V& Queue<V>::front() const
{
    if(firstNode)
        return firstNode->value;
    else
        return dummy;
}

template<typename V>
const V& Queue<V>::back() const
{
    if(lastNode)
        return lastNode->value;
    return dummy;
}

template<typename V>
void Queue<V>::pop()
{
    if(firstNode)
    {
        Node* p = firstNode;
        firstNode = firstNode->next;
        delete p;
        siz--;
    }
    if (siz == 0) lastNode = 0;
}

template<typename V>
void Queue<V>::clear()
{
    while(firstNode)
    {
        Node* p = firstNode;
        firstNode = firstNode->next; //or firstNode = p->next
        delete p;
        --siz;
    }
    
    if(siz == 0)
        lastNode = 0;
}

template<typename V>
int Queue<V>:: size() const
{
    return siz;
}

template<typename V>
bool Queue<V>:: empty() const
{
    if(siz == 0)
        return true;
    else
        return false;
}

#endif /* Queue_h */

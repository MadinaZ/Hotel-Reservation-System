#ifndef QUEUE_H_
#define QUEUE_H_

template<typename T>
void safeDelete(T*& p)
{
	delete p;
	p = 0;
}


template<typename V>
class Queue
{
	struct node
	{
		V values;
		node* next;
	};
	int siz;
	node* first;
	node* last;
	V dummy;

public:
	Queue();
	Queue(const Queue&);
	Queue<V>& operator=(const Queue<V>&);
	~Queue();
	void push(const V&);
	const V& front() const;
	const V& back() const;
	void pop();
	int size() const {return siz;}
	bool empty() const {return size() == 0;}
	void clear();
};

template<typename V>
Queue<V>::Queue()
:siz(0)
,first(0)
,last(0)
{}

template<typename V>
Queue<V>::Queue(const Queue<V>& original)
:siz(original.siz)
,first(0)
,last(0)

{
  for(node* p = original.first; p; p = p->next)
  {
    node* temp = new node;
    temp->values = p->values;
    temp->next = 0;
    // node* temp = new node{p->values,0}; C++ 11
    if(last) last->next = temp;
    else first = temp;
    last = temp;
  }
}

template<typename V>
Queue<V>& Queue<V>::operator=(const Queue<V>& original)
{
  if(this == &original) { return; }
  
  while(first)
  {
    node* p = first;
    first = first->next;
    safeDelete(p);
  }

  first = 0;
  last = 0;
  for(node* p = original.first; p; p = p->next)
  {
    node* temp = new node;
    temp->values = p->values;
    temp->next = 0;
    if(last) last->next = temp;
    else first = temp;
    last = temp;
  }
  siz = original.siz;
 
	return *this;
}

template<typename V>
Queue<V>::~Queue()
{
  while(first)
  {
    node* p = first;
    first = first->next;
    safeDelete(p);
  }
}

template<typename V>
void Queue<V>::push(const V& newvalue)
{
	node* temp = new node;

	temp->values = newvalue;
	temp->next = 0;
	if(last) last->next = temp;
	else first = temp;
	last = temp;
	siz++;

	/* C++11
	 * Node * temp = new Node{value;}
	 * if(lastNode) lastNode->next = temp;
	 * else firstNode = temp;
	 * lastNode = temp;
	 * ++siz;
	 */
}

template<typename V>
const V& Queue<V>::front() const
{
	if(first)
		return first->values;
	return dummy;
}

template<typename V>
const V& Queue<V>::back() const
{
	if(last)
		return last->values;
	return dummy;
}

template<typename V>
void Queue<V>::pop()
{
	if(first)
	{
		node* p = first;
		first = p->next;
		safeDelete(p);
		siz--;
	}
	if(siz == 0) last = 0;
}

template<typename V>
void Queue<V>::clear()
{
  while(first)
  {
    node* p = first;
    first = first->next;
    safeDelete(p);
    siz--;
  }
}

#endif /* QUEUE_H_ */

#ifndef SAFEDELETE_H
#define SAFEDELETE_H

template<typename T>
void safedeleteArray(T*& p)
{
  delete [] p;
  p = 0;
}

#endif

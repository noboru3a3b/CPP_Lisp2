// object_test.cpp

#include "object.h"

int main()
{
  Object *p, *q;
  
  p = new Object;
  p->print_addr();
  p->print();

  q = new Object;
  q->print_addr();
  q->ref_cnt++;
  q->print();

  delete p;
  delete q;

  return 0;
}


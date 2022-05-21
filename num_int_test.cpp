// num_int_test.cpp

#include <iostream>
#include "num_int.h"

int main()
{
  Object *p, *q, *r;
  
  p = new Num_int;
  p->set_value((long8)1000000000);
  p->print_addr();
  p->print();
  cout << endl;

  q = new Num_int;
  q->set_value((long8)0);
  q->print_addr();
  q->print();
  cout << endl;

  r = new Num_int;
  r->set_value((long8)-1000000000);
  r->print_addr();
  r->print();
  cout << endl;

  delete p;
  delete q;
  delete r;

  return 0;
}


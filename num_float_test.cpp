// num_float_test.cpp

#include <iostream>
#include "num_float.h"

int main()
{
  Object *p, *q, *r;
  
  p = new Num_float;
  p->set_value(5e20);
  p->print_addr();
  p->print();
  cout << endl;

  q = new Num_float;
  q->set_value(0.123456);
  q->print_addr();
  q->print();
  cout << endl;

  r = new Num_float;
  r->set_value(-6e-30);
  r->print_addr();
  r->print();
  cout << endl;

  delete p;
  delete q;
  delete r;

  return 0;
}


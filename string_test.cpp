// string_test.cpp

#include <iostream>
#include "string.h"

int main()
{
  Object *p, *q, *r;
  
  p = new String;
  p->set_value("FUJI");
  p->print_addr();
  p->print();
  cout << endl;

  q = new String;
  q->set_value("YAMA");
  q->print_addr();
  q->print();
  cout << endl;

  r = new String;
  r->set_value("PAPER MOON");
  r->print_addr();
  r->print();
  cout << endl;

  delete p;
  delete q;
  delete r;

  return 0;
}


// vector_test.cpp

#include <iostream>
#include "atom.h"
#include "vector.h"

int main()
{
  Object *p, *q, *r, *s;
  
  p = new Atom;
  p->set_name("fuji");
  p->print_addr();
  p->print();
  cout << endl;

  q = new Atom;
  q->set_name("yama");
  q->print_addr();
  q->print();
  cout << endl;

  r = new Atom;
  r->set_name("sakura");
  r->print_addr();
  r->print();
  cout << endl;

  s = new Vector(3);
  s->print_addr();

//  s->print();

  s->set_value(0, p);
  s->set_value(1, q);
  s->set_value(2, r);

  s->print();
  cout << endl;

  delete s;

  return 0;
}


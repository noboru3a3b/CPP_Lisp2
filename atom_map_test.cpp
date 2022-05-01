// atom_map_test.cpp

#include <iostream>
#include "atom_map.h"

int main()
{
  AtomMap *p;
  Object *q, *r, *s, *t;
  
  p = new AtomMap;

  q = p->get_atom("fuji");
  q->print_addr();
  q->print();
  cout << endl;

  r = p->get_atom("yama");
  r->print_addr();
  r->print();
  cout << endl;

  s = p->get_atom("t");
  s->print_addr();
  s->print();
  cout << endl;

  t = p->get_atom("nil");
  t->print_addr();
  t->print();
  cout << endl;

  delete p;
  delete q;
  delete r;
  delete s;
  delete t;

  return 0;
}


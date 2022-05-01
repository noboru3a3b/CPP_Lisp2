// atom_test.cpp

#include <iostream>
#include "atom.h"
#include "string.h"
#include "num_int.h"

int main()
{
  Object *p, *q, *r, *s, *t, *u;
  
  s = new String;
  s->set_value("string");

  t = new Num_int;
  t->set_value((long)99999999);

  u = new Atom;
  u->set_name("atom");

  p = new Atom;
  p->set_name("fuji");
  p->set_value(s);
  p->print_addr();
  p->print();
  cout << " -> ";
  p->print_value();
  cout << endl;

  q = new Atom;
  q->set_name("yama");
  q->set_value(t);
  q->print_addr();
  q->print();
  cout << " -> ";
  q->print_value();
  cout << endl;

  r = new Atom;
  r->set_name("sakura");
  r->set_value(u);
  r->print_addr();
  r->print();
  cout << " -> ";
  r->print_value();
  cout << endl;

  delete p;
  delete q;
  delete r;

  return 0;
}


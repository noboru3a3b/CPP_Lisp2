// cell_test.cpp

#include <iostream>
#include "atom.h"
#include "cell.h"

int main()
{
  Object *p, *q, *r, *s, *t, *u, *v, *w, *x, *y, *z;
  //
  // [z]--------[y]-------[x]-PON/NIL
  //  |          |         |
  // [v]-SAKURA [w]-YAMA ASAGAO
  //  |          |
  // KUWAGATA   FUJI
  //

  p = new Atom;
  p->set_name("kuwagata");

  q = new Atom;
  q->set_name("sakura");

  r = new Atom;
  r->set_name("fuji");

  s = new Atom;
  s->set_name("yama");

  t = new Atom;
  t->set_name("asagao");

  u = new Atom;
  //u->set_name("pon");
  u->set_name("nil");

  v = new Cell(p, q);
  w = new Cell(r, s);
  x = new Cell(t, u);
  y = new Cell(w, x);
  z = new Cell(v, y);

  z->print();
  cout << endl;

  delete z;

  return 0;
}


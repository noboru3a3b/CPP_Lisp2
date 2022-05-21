// full_member_test.cpp

#include <iostream>
#include "atom.h"
#include "string.h"
#include "num_int.h"
#include "num_float.h"
#include "cell.h"

int main()
{
  Object *p, *q, *r, *s, *t, *u, *v, *w, *x, *y, *z;

  //
  // [z]----------[y]---------[x]- -0.001234
  //  |            |           |
  // [v]- -100000 [w]- -5e-15 NIL
  //  |            |
  // SAKURA   "PAPER MOON"
  //

  p = new Atom;
  p->set_name("sakura");

  q = new Num_int;
  q->set_value((long8 )-100000);

  r = new String;
  r->set_value("PAPER MOON");

  s = new Num_float;
  s->set_value(-5e-15);

  t = new Atom;
  t->set_name("nil");

  u = new Num_float;
  u->set_value(-0.001234);

  v = new Cell;
  w = new Cell;
  x = new Cell;
  y = new Cell;
  z = new Cell;

  v->set_car( p );
  v->set_cdr( q );

  w->set_car( r );
  w->set_cdr( s );

  x->set_car( t );
  x->set_cdr( u );

  y->set_car( w );
  y->set_cdr( x );

  z->set_car( v );
  z->set_cdr( y );

  z->print();
  cout << endl;

  delete z;

  return 0;
}


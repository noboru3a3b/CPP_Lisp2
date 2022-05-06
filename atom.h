// atom.h

#ifndef __ATOM_H__
#define __ATOM_H__

#include "object.h"
#include <string>

using namespace std;

class Atom : public Object
{
 public:
  string name;
  Object *value;
  Object *(*func)(Object *e, Object *a);

  Atom();
  ~Atom();

  void print();
  void print_value();
  void print_car();
  void print_cdr();
  void set_name( string s );
  void set_value( Object *v );
  void set_func( Object *(*fn)(Object *e, Object *a) );
};

#endif // __ATOM_H__

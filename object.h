// object.h

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>

using namespace std;

class Object
{
 public:
  unsigned long ref_cnt;

  Object();
  virtual ~Object();

  void print_addr();
  virtual void print();

  // for Atom
  virtual void set_name(string s);
  virtual void set_value(Object *v);
  virtual void print_value();

  // for String
  virtual void set_value(string s);

  // for Num_int
  virtual void set_value(long n);

  // for Num_float
  virtual void set_value(double n);

  // for Cell
  virtual void print_car();
  virtual void print_cdr();
  virtual void set_car(Object *p);
  virtual void set_cdr(Object *p);

  // for Vector
  virtual long get_size();
  virtual void set_value(long i, Object *p);
  virtual Object *get_value(long i);
};

#endif // __OBJECT_H__

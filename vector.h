// vector.h

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "object.h"

using namespace std;

class Vector  : public Object
{
 public:
  long size;
  Object **vector;
  
  Vector( long n );
  ~Vector();
  
  void print();
  void print_car();
  void print_cdr();
  long get_size();
  void set_value(long i, Object *p);
  Object *get_value(long i);
};

#endif // __VECTOR_H__


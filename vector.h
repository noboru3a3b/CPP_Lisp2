// vector.h

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "object.h"

using namespace std;

class Vector  : public Object
{
 public:
  long8 size;
  Object **vector;
  
  Vector( long8 n );
  ~Vector();
  
  void print();
  void print_car();
  void print_cdr();
  long8 get_size();
  void set_value(long8 i, Object *p);
  Object *get_value(long8 i);
};

#endif // __VECTOR_H__


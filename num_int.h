// num_int.h

#ifndef __NUM_INT_H__
#define __NUM_INT_H__

#include "object.h"

using namespace std;

class Num_int  : public Object
{
 public:
  long8 value;
  
  Num_int();
  ~Num_int();
  
  void print();
  void print_car();
  void print_cdr();
  void set_value(long8 n);
};

#endif // __NUM_INT_H__


// num_float.h

#ifndef __NUM_FLOAT_H__
#define __NUM_FLOAT_H__

#include "object.h"

using namespace std;

class Num_float  : public Object
{
 public:
  double value;
  
  Num_float();
  ~Num_float();
  
  void print();
  void print_car();
  void print_cdr();
  void set_value(double n);
};

#endif // __NUM_FLOAT_H__


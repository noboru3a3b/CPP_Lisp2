// float_map.h

#ifndef __FLOAT_MAP_H__
#define __FLOAT_MAP_H__

#include "num_float.h"
#include <map>
#include <string>

using namespace std;

class FloatMap
{
 public:
  map<double, Num_float *> float_map;
  
  FloatMap();
  ~FloatMap();
  
  Num_float *get_float(double n);
  int print_all();
  int delete_free_floats();
};

#endif // __FLOAT_MAP_H__


// int_map.h

#ifndef __INT_MAP_H__
#define __INT_MAP_H__

#include "num_int.h"
#include <map>
#include <string>

using namespace std;

class IntMap
{
 public:
  map<long8, Num_int *> int_map;
  
  IntMap();
  ~IntMap();
  
  Num_int *get_int(long8 n);
  int print_all();
  int delete_free_ints();
};

#endif // __INT_MAP_H__


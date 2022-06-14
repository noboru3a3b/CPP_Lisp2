// vector_map.h

#ifndef __VECTOR_MAP_H__
#define __VECTOR_MAP_H__

#include "vector.h"
#include <map>
#include <string>

using namespace std;

class VectorMap
{
 public:
  map<long8, Vector *> vector_map;
  
  VectorMap();
  ~VectorMap();
  
  Vector *get_vector(long8 i);
  int print_all();
  int delete_free_vectors();
};

#endif // __VECTOR_MAP_H__


// string_map.h

#ifndef __STRING_MAP_H__
#define __STRING_MAP_H__

#include "string.h"
#include <map>
#include <string>

using namespace std;

class StringMap
{
 public:
  map<string, String *> string_map;
  
  StringMap();
  ~StringMap();
  
  String *get_string(string s);
  int print_all();
  int delete_free_strings();
};

#endif // __STRING_MAP_H__


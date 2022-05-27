// string.h

#ifndef __STRING_H__
#define __STRING_H__

#include "object.h"
#include <string>

using namespace std;

class String  : public Object
{
 public:
  string value;
  
  String();
  String(string s);
  ~String();
  
  void print();
  void print_car();
  void print_cdr();
  void set_value(string s);
};

#endif // __STRING_H__


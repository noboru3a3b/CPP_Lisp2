// cell.h

#ifndef __CELL_H__
#define __CELL_H__

#include "object.h"

using namespace std;

class Cell  : public Object
{
 public:
  Object *car;
  Object *cdr;
  
  Cell();
  Cell(Object *car, Object *cdr);
  ~Cell();
  
  void print();
  void print_car();
  void print_cdr();
  void set_car(Object *p);
  void set_cdr(Object *p);
};

#endif // __CELL_H__


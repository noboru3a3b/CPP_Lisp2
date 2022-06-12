// cell_map.h

#ifndef __CELL_MAP_H__
#define __CELL_MAP_H__

#include "cell.h"
#include <map>
#include <string>

using namespace std;

class CellMap
{
 public:
  map<long8, Cell *> cell_map;
  
  CellMap();
  ~CellMap();
  
  Cell *get_cell();
  Cell *get_cell(Object *, Object *);
  int print_all();
  int delete_free_cells();
};

#endif // __CELL_MAP_H__


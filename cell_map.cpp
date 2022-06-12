// cell_map.cpp

#include <iostream>
#include "cell_map.h"

// Output FILE Stream
extern ofstream ofs;
extern bool ofs_on;
extern bool cout_on;

CellMap::CellMap()
{

}

CellMap::~CellMap()
{

}

Cell *CellMap::get_cell()
{
  Cell *c;

  // new Cell
  c = new Cell();
  cell_map[(long8)c] = c;
  cell_map[(long8)c]->ref_cnt++;	// by Reference from CellMap

  return c;
}

Cell *CellMap::get_cell(Object *p, Object *q)
{
  Cell *c;

  // new Cell
  c = new Cell(p, q);
  cell_map[(long8)c] = c;
  cell_map[(long8)c]->ref_cnt++;	// by Reference from CellMap

  return c;
}

int CellMap::print_all()
{
  int i = 0;

  for (auto itr = cell_map.begin(); itr != cell_map.end(); ++itr)
  {
    if (cout_on) {cout << itr->first << ":" << (itr->second)->ref_cnt << " ";}
    if (ofs_on) {ofs << itr->first << ":" << (itr->second)->ref_cnt << " ";}

    if ((i % 10) == 9)
    {
      if (cout_on) {cout << endl;}
      if (ofs_on) {ofs << endl;}
    }
    i++;
  }

  if ((i % 10) != 0)
  {
    if (cout_on) {cout << endl;}
    if (ofs_on) {ofs << endl;}
  }

  return i;
}

int CellMap::delete_free_cells()
{
  int i = 0;
  Object *save;

  for (auto itr = cell_map.begin(); itr != cell_map.end();)
  {
    // delete free_cells
    if ((itr->second)->ref_cnt < 2)
    {
//      if (cout_on) {cout << itr->first << ":" << (itr->second)->ref_cnt << " ";}
//      if (ofs_on) {ofs << itr->first << ":" << (itr->second)->ref_cnt << " ";}

      save = itr->second;

      itr = cell_map.erase(itr);  // Unregist itr, get next element of itr
      delete save;                // Delete unregistered element

      if ((i % 10) == 9)
      {
//        if (cout_on) {cout << endl;}
//        if (ofs_on) {ofs << endl;}
      }
      i++;
    }
    else
    {
      ++itr;
    }
  }

  if ((i % 10) != 0)
  {
//    if (cout_on) {cout << endl;}
//    if (ofs_on) {ofs << endl;}
  }

  return i;
}

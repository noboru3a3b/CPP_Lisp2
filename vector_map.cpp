// vector_map.cpp

#include <iostream>
#include "vector_map.h"

// Output FILE Stream
extern ofstream ofs;
extern bool ofs_on;
extern bool cout_on;

VectorMap::VectorMap()
{

}

VectorMap::~VectorMap()
{

}

Vector *VectorMap::get_vector( long8 n )
{
  Vector *v;

  // new Vector
  v = new Vector(n);
  vector_map[(long8)v] = v;
  vector_map[(long8)v]->ref_cnt++;	// by Reference from VectorMap

  return v;
}

int VectorMap::print_all()
{
  int i = 0;

  for (auto itr = vector_map.begin(); itr != vector_map.end(); ++itr)
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

int VectorMap::delete_free_vectors()
{
  int i = 0;
  Object *save;

  for (auto itr = vector_map.begin(); itr != vector_map.end();)
  {
    // delete free_vectors
    if ((itr->second)->ref_cnt < 2)
    {
//      if (cout_on) {cout << itr->first << ":" << (itr->second)->ref_cnt << " ";}
//      if (ofs_on) {ofs << itr->first << ":" << (itr->second)->ref_cnt << " ";}

      save = itr->second;

      itr = vector_map.erase(itr);  // Unregist itr, get next element of itr
      delete save;                  // Delete unregistered element

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

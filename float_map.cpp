// float_map.cpp

#include <iostream>
#include "float_map.h"

// Output FILE Stream
extern ofstream ofs;
extern bool ofs_on;
extern bool cout_on;

FloatMap::FloatMap()
{

}

FloatMap::~FloatMap()
{

}

Num_float *FloatMap::get_float(double n)
{
  if (float_map.find(n) == float_map.end())
  {
    // new float
    float_map[n] = new Num_float(n);
    float_map[n]->ref_cnt++;	// by Reference from FloatMap
  }
  else
  {
    // already exists
  }

  return float_map[n];
}

int FloatMap::print_all()
{
  int i = 0;

  for (auto itr = float_map.begin(); itr != float_map.end(); ++itr)
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

int FloatMap::delete_free_floats()
{
  int i = 0;
  Object *save;

  for (auto itr = float_map.begin(); itr != float_map.end();)
  {
    // delete free_floats
    if ((itr->second)->ref_cnt < 2)
    {
      if (cout_on) {cout << itr->first << ":" << (itr->second)->ref_cnt << " ";}
      if (ofs_on) {ofs << itr->first << ":" << (itr->second)->ref_cnt << " ";}

      save = itr->second;

      itr = float_map.erase(itr); // Unregist itr, get next element of itr
      delete save;                // Delete unregistered element

      if ((i % 10) == 9)
      {
        if (cout_on) {cout << endl;}
        if (ofs_on) {ofs << endl;}
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
    if (cout_on) {cout << endl;}
    if (ofs_on) {ofs << endl;}
  }

  return i;
}

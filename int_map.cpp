// int_map.cpp

#include <iostream>
#include "int_map.h"

// Output FILE Stream
extern ofstream ofs;
extern bool ofs_on;
extern bool cout_on;

IntMap::IntMap()
{

}

IntMap::~IntMap()
{

}

Num_int *IntMap::get_int(long8 n)
{
  if (int_map.find(n) == int_map.end())
  {
    // new int
    int_map[n] = new Num_int(n);
    int_map[n]->ref_cnt++;	// by Reference from IntMap
  }
  else
  {
    // already exists
  }

  return int_map[n];
}

int IntMap::print_all()
{
  int i = 0;

  for (auto itr = int_map.begin(); itr != int_map.end(); ++itr)
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

int IntMap::delete_free_ints()
{
  int i = 0;
  Object *save;

  for (auto itr = int_map.begin(); itr != int_map.end();)
  {
    // delete free_ints
    if ((itr->second)->ref_cnt < 2)
    {
      if (cout_on) {cout << itr->first << ":" << (itr->second)->ref_cnt << " ";}
      if (ofs_on) {ofs << itr->first << ":" << (itr->second)->ref_cnt << " ";}

      save = itr->second;

      itr = int_map.erase(itr); // Unregist itr, get next element of itr
      delete save;              // Delete unregistered element

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

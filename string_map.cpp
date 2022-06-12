// string_map.cpp

#include <iostream>
#include "string_map.h"

// Output FILE Stream
extern ofstream ofs;
extern bool ofs_on;
extern bool cout_on;

StringMap::StringMap()
{

}

StringMap::~StringMap()
{

}

String *StringMap::get_string(string s)
{
  if (string_map.find(s) == string_map.end())
  {
    // new String
    string_map[s] = new String(s);
    string_map[s]->ref_cnt++;	// by Reference from StringMap
  }
  else
  {
    // already exists
  }

  return string_map[s];
}

int StringMap::print_all()
{
  int i = 0;

  for (auto itr = string_map.begin(); itr != string_map.end(); ++itr)
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

int StringMap::delete_free_strings()
{
  int i = 0;
  Object *save;

  for (auto itr = string_map.begin(); itr != string_map.end();)
  {
    // delete free_strings
    if ((itr->second)->ref_cnt < 2)
    {
//      if (cout_on) {cout << itr->first << ":" << (itr->second)->ref_cnt << " ";}
//      if (ofs_on) {ofs << itr->first << ":" << (itr->second)->ref_cnt << " ";}

      save = itr->second;

      itr = string_map.erase(itr);  // Unregist itr, get next element of itr
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

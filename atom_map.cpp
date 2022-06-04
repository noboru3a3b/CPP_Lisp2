// atom_map.cpp

#include <iostream>
#include "atom_map.h"

// Output FILE Stream
extern ofstream ofs;
extern bool ofs_on;
extern bool cout_on;

AtomMap::AtomMap()
{

}

AtomMap::~AtomMap()
{

}

Atom *AtomMap::get_atom(string s)
{
  if (atom_map.find(s) == atom_map.end())
  {
    // new atom
    atom_map[s] = new Atom;
    atom_map[s]->set_name(s);
    atom_map[s]->ref_cnt++;	// by Reference from AtomMap
  }
  else
  {
    // already exists
  }

  return atom_map[s];
}

int AtomMap::print_all()
{
  int i = 0;

  for (auto itr = atom_map.begin(); itr != atom_map.end(); ++itr)
  {
    if (cout_on) {cout << itr->first << " ";}
    if (ofs_on) {ofs << itr->first << " ";}

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

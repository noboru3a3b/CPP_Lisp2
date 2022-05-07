// atom_map.cpp

#include <iostream>
#include "atom_map.h"

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
//      atom_map[s]->ref_cnt++;
    }
  return atom_map[s];
}

void AtomMap::print_all()
{
  int i = 0;

  cout << " ---------- atoms ---------- " << endl;
  for (auto itr = atom_map.begin(); itr != atom_map.end(); ++itr)
  {
    cout << itr->first << " ";
    if ((i % 10) == 9)
    {
      cout << endl;
    }
    i++;
  }

  if ((i % 10) != 0)
  {
    cout << endl;
  }
}

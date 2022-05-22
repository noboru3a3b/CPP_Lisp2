// atom_map.h

#ifndef __ATOM_MAP_H__
#define __ATOM_MAP_H__

#include "atom.h"
#include <map>
#include <string>

using namespace std;

class AtomMap
{
 public:
  map<string, Atom *> atom_map;
  
  AtomMap();
  ~AtomMap();
  
  Atom *get_atom(string s);
  int print_all();
};

#endif // __ATOM_MAP_H__


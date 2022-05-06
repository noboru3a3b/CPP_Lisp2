// atom.cpp

#include <iostream>
#include "atom.h"

Atom::Atom()
{
  value = NULL;
  func = NULL;
}

Atom::~Atom()
{
  if (value != NULL)
  {
    value->ref_cnt--;
    if (value->ref_cnt == 0) delete value;
  }
}

void Atom::print()
{
  //  cout << "name=" << name << endl;
  cout << name;
}

void Atom::print_value()
{
  value->print();
}

void Atom::print_car()
{
  cout << name;
}

void Atom::print_cdr()
{
  if (name == "nil")
  {
    cout << ")";
  }
  else
  {
    cout << " . " << name << ")";
  }
}

void Atom::set_name(string s)
{
  name = s;
}

void Atom::set_value(Object *v)
{
  value = v;
  value->ref_cnt++;
}

void Atom::set_func(Object *(*fn)(Object *e, Object *))
{
  func = fn;
  value->ref_cnt++;
}

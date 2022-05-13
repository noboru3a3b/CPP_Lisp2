// atom.cpp

#include <iostream>
#include "atom.h"

Atom::Atom()
{
  value = NULL;
  lambda = NULL;
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
  if (value != NULL)
  {
    value->ref_cnt--;
  }

  value = v;
  v->ref_cnt++;
}

void Atom::set_lambda(Object *lmd)
{
  if (lambda != NULL)
  {
    lambda->ref_cnt--;
  }

  lambda = lmd;
  lmd->ref_cnt++;
}

void Atom::set_func(Object *(*fn)(Object *e, Object *))
{
  func = fn;
}

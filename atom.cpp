// atom.cpp

#include <iostream>
#include "atom.h"

// Output FILE Stream
extern ofstream ofs;
extern bool ofs_on;
extern bool cout_on;

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

  if (lambda != NULL)
  {
    lambda->ref_cnt--;
    if (lambda->ref_cnt == 0) delete lambda;
  }
}

void Atom::print()
{
  if (cout_on) {cout << name;}
  if (ofs_on) {ofs << name;}
}

void Atom::print_value()
{
  value->print();
}

void Atom::print_car()
{
  if (cout_on) {cout << name;}
  if (ofs_on) {ofs << name;}
}

void Atom::print_cdr()
{
  if (name == "nil")
  {
    if (cout_on) {cout << ")";}
    if (ofs_on) {ofs << ")";}
  }
  else
  {
    if (cout_on) {cout << " . " << name << ")";}
    if (ofs_on) {ofs << " . " << name << ")";}
  }
}

void Atom::set_name(string s)
{
  name = s;
}

void Atom::set_value(Object *v)
{
  Object *save;

  if (value != NULL)
  {
    // Write Same Object
    if (value == v)
    {
      // Do nothing
      return;
    }

    save = value;

    value = v;
    value->ref_cnt++;

    save->ref_cnt--;
    if (save->ref_cnt == 0) delete save;
    return;
  }

  value = v;
  value->ref_cnt++;
}

void Atom::set_lambda(Object *lmd)
{
  Object *save;

  if (lambda != NULL)
  {
    // Write Same Function
    if (lambda == lmd)
    {
      // Do nothing
      return;
    }

    save = lambda;
  
    lambda = lmd;
    lambda->ref_cnt++;

    save->ref_cnt--;
    if (save->ref_cnt == 0) delete save;
    return;
  }

  lambda = lmd;
  lambda->ref_cnt++;
}

void Atom::set_func(Object *(*fn)(Object *e, Object *))
{
  func = fn;
}

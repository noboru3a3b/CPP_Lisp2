// vector.cpp

#include <iostream>
#include "vector.h"

// Output FILE Stream
extern ofstream ofs;
extern bool ofs_on;
extern bool cout_on;

Vector::Vector(long8 n)
{
  size = n;
  vector = new Object * [size];

  for (long8 i = 0; i < size; i++)
  {
    vector[i] = NULL;
  }
}

Vector::~Vector()
{
  for (long8 i = 0; i < size; i++)
  {
    if (vector[i] != NULL)
    {
      vector[i]->ref_cnt--;
      if (vector[i]->ref_cnt == 0) delete vector[i];
    }
  }
  delete[] vector;
}

void Vector::print()
{
  if (cout_on) {cout << "#(";}
  if (ofs_on) {ofs << "#(";}

  for (long8 i = 0; i < size; i++)
  {
    if (i > 0) if (cout_on) {cout << " ";}
    if (i > 0) {if (ofs_on) {ofs << " ";}}

    vector[i]->print();
  }

  if (cout_on) {cout << ")";}
  if (ofs_on) {ofs << ")";}
}

void Vector::print_car()
{
  if (cout_on) {cout << "#(";}
  if (ofs_on) {ofs << "#(";}

  for (long8 i = 0; i < size; i++)
  {
    if (i > 0) if (cout_on) {cout << " ";}
    if (i > 0) {if (ofs_on) {ofs << " ";}}
 
    vector[i]->print();
  }

  if (cout_on) {cout << ")";}
  if (ofs_on) {ofs << ")";}
}

void Vector::print_cdr()
{
  if (cout_on) {cout << " . ";}
  if (ofs_on) {ofs << " . ";}

  {
    if (cout_on) {cout << "#(";}
    if (ofs_on) {ofs << "#(";}
  
    for (long8 i = 0; i < size; i++)
    {
      if (i > 0) if (cout_on) {cout << " ";}
      if (i > 0) {if (ofs_on) {ofs << " ";}}

      vector[i]->print();
    }

    if (cout_on) {cout << ")";}
    if (ofs_on) {ofs << ")";}
  }

  if (cout_on) {cout << ")";}
  if (ofs_on) {ofs << ")";}
}

long8 Vector::get_size()
{
  return size;
}

void Vector::set_value(long8 i, Object *p)
{
  Object *save;

  if (vector[i] != NULL)
  {
    // Write Same Object
    if (vector[i] == p)
    {
      // Do nothing
      return;
    }

    save = vector[i];

    vector[i] = p;
    p->ref_cnt++;

    save->ref_cnt--;
    if (save->ref_cnt == 0) delete save;
    return;
  }

  vector[i] = p;
  p->ref_cnt++;
}

Object *Vector::get_value(long8 i)
{
  return vector[i];
}


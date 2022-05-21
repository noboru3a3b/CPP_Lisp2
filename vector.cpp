// vector.cpp

#include <iostream>
#include "vector.h"

Vector::Vector(long8 n)
{
  size = n;
  vector = new Object * [size];
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
  cout << "#(";
  for (long8 i = 0; i < size; i++)
  {
    if (i > 0) cout << " ";
    vector[i]->print();
  }
  cout << ")";
}

void Vector::print_car()
{
  cout << "#(";
  for (long8 i = 0; i < size; i++)
  {
    if (i > 0) cout << " ";
    vector[i]->print();
  }
  cout << ")";
}

void Vector::print_cdr()
{
  cout << " . ";
  {
    cout << "#(";
    for (long8 i = 0; i < size; i++)
    {
      if (i > 0) cout << " ";
      vector[i]->print();
    }
    cout << ")";
  }
  cout << ")";
}

long8 Vector::get_size()
{
  return size;
}

void Vector::set_value(long8 i, Object *p)
{
  vector[i] = p;
  p->ref_cnt++;
}

Object *Vector::get_value(long8 i)
{
  return vector[i];
}


// vector.cpp

#include <iostream>
#include "vector.h"

Vector::Vector(long n)
{
  size = n;
  vector = new Object * [size];
}

Vector::~Vector()
{
  for (long i = 0; i < size; i++)
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
  for (long i = 0; i < size; i++)
  {
    if (i > 0) cout << " ";
    vector[i]->print();
  }
  cout << ")";
}

void Vector::print_car()
{
  cout << "#(";
  for (long i = 0; i < size; i++)
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
    for (long i = 0; i < size; i++)
    {
      if (i > 0) cout << " ";
      vector[i]->print();
    }
    cout << ")";
  }
  cout << ")";
}

long Vector::get_size()
{
  return size;
}

void Vector::set_value(long i, Object *p)
{
  vector[i] = p;
  p->ref_cnt++;
}

Object *Vector::get_value(long i)
{
  return vector[i];
}


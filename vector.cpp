// vector.cpp

#include <iostream>
#include "vector.h"

// Output FILE Stream
extern ofstream ofs;
extern bool ofs_on;

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
  if (ofs_on) {ofs << "#(";}

  for (long8 i = 0; i < size; i++)
  {
    if (i > 0) cout << " ";
    if (i > 0) {if (ofs_on) {ofs << " ";}}

    vector[i]->print();
  }
  cout << ")";
  if (ofs_on) {ofs << ")";}
}

void Vector::print_car()
{
  cout << "#(";
  if (ofs_on) {ofs << "#(";}

  for (long8 i = 0; i < size; i++)
  {
    if (i > 0) cout << " ";
    if (i > 0) {if (ofs_on) {ofs << " ";}}
 
    vector[i]->print();
  }
  cout << ")";
  if (ofs_on) {ofs << ")";}
}

void Vector::print_cdr()
{
  cout << " . ";
  if (ofs_on) {ofs << " . ";}

  {
    cout << "#(";
    if (ofs_on) {ofs << "#(";}
  
    for (long8 i = 0; i < size; i++)
    {
      if (i > 0) cout << " ";
      if (i > 0) {if (ofs_on) {ofs << " ";}}

      vector[i]->print();
    }
    cout << ")";
    if (ofs_on) {ofs << ")";}
  }
  cout << ")";
  if (ofs_on) {ofs << ")";}
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


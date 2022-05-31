// num_float.cpp

#include <iostream>
#include "num_float.h"

// Output FILE Stream
extern ofstream ofs;
extern bool ofs_on;
extern bool cout_on;

Num_float::Num_float()
{

}

Num_float::Num_float(double n)
{
  value = n;
}

Num_float::~Num_float()
{

}

void Num_float::print()
{
  if (cout_on) {cout << value;}
  if (ofs_on) {ofs << value;}
}

void Num_float::print_car()
{
  if (cout_on) {cout << value;}
  if (ofs_on) {ofs << value;}
}

void Num_float::print_cdr()
{
  if (cout_on) {cout << " . " << value << ")";}
  if (ofs_on) {ofs << " . " << value << ")";}
}

void Num_float::set_value(double n)
{
  value = n;
}


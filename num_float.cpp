// num_float.cpp

#include <iostream>
#include "num_float.h"

Num_float::Num_float()
{

}

Num_float::~Num_float()
{

}

void Num_float::print()
{
  cout << value;
}

void Num_float::print_car()
{
  cout << value;
}

void Num_float::print_cdr()
{
  cout << " . " << value << ")";
}

void Num_float::set_value(double n)
{
  value = n;
}


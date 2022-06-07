// num_int.cpp

#include <iostream>
#include "num_int.h"

// Output FILE Stream
extern ofstream ofs;
extern bool ofs_on;
extern bool cout_on;

Num_int::Num_int()
{

}

Num_int::Num_int(long8 n)
{
  value = n;
//  cout << " [iSET " << value << ":" << ref_cnt << "] ";
}

Num_int::~Num_int()
{
//  cout << " [iDEL " << value << ":" << ref_cnt << "] ";
}

void Num_int::print()
{
  if (cout_on) {cout << value;}
  if (ofs_on) {ofs << value;}
}

void Num_int::print_car()
{
  if (cout_on) {cout << value;}
  if (ofs_on) {ofs << value;}
}

void Num_int::print_cdr()
{
  if (cout_on) {cout << " . " << value << ")";}
  if (ofs_on) {ofs << " . " << value << ")";}
}

void Num_int::set_value(long8 n)
{
  value = n;
//  cout << " [iSET2 " << value << ":" << ref_cnt << "] ";
}


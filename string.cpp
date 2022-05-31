// atom.cpp

#include <iostream>
#include "string.h"

// Output FILE Stream
extern ofstream ofs;
extern bool ofs_on;
extern bool cout_on;

String::String()
{

}

String::String(string s)
{
  value = s;
}

String::~String()
{

}

void String::print()
{
  if (cout_on) {cout << "\"" << value << "\"";}
  if (ofs_on) {ofs << "\"" << value << "\"";}
}

void String::print_car()
{
  if (cout_on) {cout << "\"" << value << "\"";}
  if (ofs_on) {ofs << "\"" << value << "\"";}
}

void String::print_cdr()
{
  if (cout_on) {cout << " . " << "\"" << value << "\"" << ")";}
  if (ofs_on) {ofs << " . " << "\"" << value << "\"" << ")";}
}

void String::set_value(string s)
{
  value = s;
}


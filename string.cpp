// atom.cpp

#include <iostream>
#include "string.h"

String::String()
{

}

String::~String()
{

}

void String::print()
{
  cout << "\"" << value << "\"";
}

void String::print_car()
{
  cout << "\"" << value << "\"";
}

void String::print_cdr()
{
  cout << " . " << "\"" << value << "\"" << ")";
}

void String::set_value(string s)
{
  value = s;
}


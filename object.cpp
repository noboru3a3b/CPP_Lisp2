// object.cpp

#include <iostream>
#include "object.h"

Object::Object()
{
  ref_cnt = 0;
}

Object::~Object()
{

}

void Object::print_addr()
{
  cout << "address=" << this << endl;
}

void Object::print()
{
  cout << "ref_cnt=" << ref_cnt << endl;
}

// for Atom
void Object::set_name(string s)
{

}
void Object::set_value(Object *v)
{

}

void Object::print_value()
{

}

// for String
void Object::set_value(string s)
{

}

// for Num_int
void Object::set_value(long n)
{

}

// for Num_float
void Object::set_value(double n)
{

}

// for Cell
void Object::print_car()
{

}

void Object::print_cdr()
{

}

void Object::set_car(Object *p)
{

}

void Object::set_cdr(Object *p)
{

}

// for Vector
long Object::get_size()
{
  return 0;
}

void Object::set_value(long i, Object *p)
{

}

Object *Object::get_value(long i)
{
  return NULL;
}

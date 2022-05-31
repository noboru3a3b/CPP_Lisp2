// object.cpp

#include <iostream>
#include "object.h"

// Output FILE Stream
extern ofstream ofs;
extern bool ofs_on;
extern bool cout_on;

Object::Object()
{
  ref_cnt = 0;
}

Object::~Object()
{

}

void Object::print_addr()
{
  if (cout_on) {cout << "address=" << this << endl;}
  if (ofs_on) {ofs << "address=" << this << endl;}
}

void Object::print()
{
  if (cout_on) {cout << "ref_cnt=" << ref_cnt << endl;}
  if (ofs_on) {ofs << "ref_cnt=" << ref_cnt << endl;}
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
void Object::set_value(long8 n)
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
long8 Object::get_size()
{
  return 0;
}

void Object::set_value(long8 i, Object *p)
{

}

Object *Object::get_value(long8 i)
{
  return NULL;
}

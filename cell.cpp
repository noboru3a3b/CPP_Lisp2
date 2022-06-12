// cell.cpp

#include <iostream>
#include "cell.h"

// Output FILE Stream
extern ofstream ofs;
extern bool ofs_on;
extern bool cout_on;

using namespace std;

Cell::Cell()
{
  car = NULL;
  cdr = NULL;
}

Cell::Cell(Object *p, Object *q)
{
  car = p;
  cdr = q;
  car->ref_cnt++;
  cdr->ref_cnt++;
}

Cell::~Cell()
{
//  if (cout_on) {cout << "[DEL this()] ";}
//  if (ofs_on) {ofs << "[DEL this()] ";}

  car->ref_cnt--;
  cdr->ref_cnt--;

  if (car->ref_cnt == 0)
  {
//    if (cout_on) {cout << "[DEL car()] ";}
//    if (ofs_on) {ofs << "[DEL car()] ";}
    delete car;
  }

  if (cdr->ref_cnt == 0)
  {
//    if (cout_on) {cout << "[DEL cdr()] ";}
//    if (ofs_on) {ofs << "[DEL cdr()] ";}
    delete cdr;
  }
}

void Cell::print()
{
  if (cout_on) {cout << "(";}
  if (ofs_on) {ofs << "(";}

  car->print_car();
  cdr->print_cdr();
}

void Cell::print_car()
{
  if (cout_on) {cout << "(";}
  if (ofs_on) {ofs << "(";}

  car->print_car();
  cdr->print_cdr();
}

void Cell::print_cdr()
{
  if (cout_on) {cout << " ";}
  if (ofs_on) {ofs << " ";}

  car->print_car();
  cdr->print_cdr();
}

void Cell::set_car(Object *p)
{
  Object *save;

  if (car != NULL)
  {
    // Write Other Object
    if (car != p)
    {
      save = car;

      car = p;
      car->ref_cnt++;

      save->ref_cnt--;
      if (save->ref_cnt == 0)
      {
        delete save;
      }
    }
  }
  // First Write
  else
  {
    car = p;
    car->ref_cnt++;
  }
}

void Cell::set_cdr(Object *p)
{
  Object *save;

  if (cdr != NULL)
  {
    // Write Other Object
    if (cdr != p)
    {
      save = cdr;

      cdr = p;
      cdr->ref_cnt++;

      save->ref_cnt--;
      if (save->ref_cnt == 0)
      {
        delete save;
      }
    }
  }
  // First Write
  else
  {
    cdr = p;
    cdr->ref_cnt++;
  }
}

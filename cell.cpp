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
  car->ref_cnt--;
  cdr->ref_cnt--;
  if (car->ref_cnt == 0) delete car;
  if (cdr->ref_cnt == 0) delete cdr;
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
  if (car != NULL)
  {
    car->ref_cnt--;
  }

  car = p;
  car->ref_cnt++;
}

void Cell::set_cdr(Object *p)
{
  if (cdr != NULL)
  {
    cdr->ref_cnt--;
  }

  cdr = p;
  cdr->ref_cnt++;
}

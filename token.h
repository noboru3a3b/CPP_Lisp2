// token.h

#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <string>
#include "type.h"

using namespace std;

struct Token
{
  string str;
  Type type;
};

#endif // __TOKEN_H__


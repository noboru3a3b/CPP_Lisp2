// read_test.cpp

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

#include "type.h"
#include "token.h"
#include "atom.h"
#include "string.h"
#include "num_int.h"
#include "num_float.h"
#include "cell.h"
#include "vector.h"
#include "atom_map.h"

Object *s_read(vector<Token> *tokens, int idx, int *rest_idx);
Object *s_cdr_read(vector<Token> *tokens, int idx, int *rest_idx);

void v_rest_read(Object *v, int i, vector<Token> *tokens, int idx, int *rest_idx);
void v_rest_skip(vector<Token> *tokens, int idx, int *rest_idx);

Object *s_eval(Object *e, Object *a);

using namespace std;

AtomMap *mp = new AtomMap;

// Create Atoms
Atom *p_t = mp->get_atom("t");
Atom *p_nil = mp->get_atom("nil");

Atom *p_quote = mp->get_atom("quote");
Atom *p_atom = mp->get_atom("atom");
Atom *p_eq = mp->get_atom("eq");
Atom *p_car = mp->get_atom("car");
Atom *p_cdr = mp->get_atom("cdr");
Atom *p_cons = mp->get_atom("cons");
Atom *p_cond = mp->get_atom("cond");
Atom *p_lambda = mp->get_atom("lambda");
Atom *p_label = mp->get_atom("label");

Atom *p_caar = mp->get_atom("caar");
Atom *p_cadr = mp->get_atom("cadr");
Atom *p_cadar = mp->get_atom("cadar");
Atom *p_caddr = mp->get_atom("caddr");
Atom *p_caddar = mp->get_atom("caddar");
Atom *p_list = mp->get_atom("list");
Atom *p_null = mp->get_atom("null");
Atom *p_and = mp->get_atom("and");
Atom *p_not = mp->get_atom("not");
Atom *p_append = mp->get_atom("append");
Atom *p_pair = mp->get_atom("pair");
Atom *p_assoc = mp->get_atom("assoc");

Atom *p_evcon = mp->get_atom("evcon");
Atom *p_evlis = mp->get_atom("evlis");
Atom *p_eval = mp->get_atom("eval");

Atom *p_aaa = mp->get_atom("aaa");
Atom *p_bbb = mp->get_atom("bbb");

// Create Type_IDs
const type_info& id_Atom = typeid(Atom);
const type_info& id_String = typeid(String);
const type_info& id_Num_int = typeid(Num_int);
const type_info& id_Num_float = typeid(Num_float);
const type_info& id_Cell = typeid(Cell);
const type_info& id_Vector = typeid(Vector);


// --------------- Get Text for One S-Expression ---------------

// abc                             (Atom)
// 123 -123                        (Int)
// 1.23 -1.23 1.23e10 -1.23e-10    (Float)
// "ABC"                           (String)
// (...)                           (List)
// 'ABC '(...)                     (quote)
// #(1 2 3)                        (Vector)
// #'(...)                         (function ())

//
// 標準入力からS式1個分の文字列を読み込む
//
// 正しいS式が入力されることを期待している。
// 括弧の数を確認していて、閉じ括弧の方が少ない間は、
// さらに1行読み、閉じ括弧の数が一致するか多くなるまで
// 読み続ける。
// 読んだ全行を連結して、1つのstringとして返す。
//

string s_input()
{
  char str[256];
  string line_text;
  string s_text = "";
  int leftp_cnt = 0;
  int rightp_cnt = 0;
  int text_size;
  int in_string = 0;

  do
  {
    cout << "> ";
    cin.getline(str, 256);
    line_text = str;
    text_size = line_text.size();

    for (int i = 0; i < text_size; i++)
    {
      // In String
      if (in_string != 0)
      {
        // Close String
        if (line_text[i] == '"')
        {
          in_string = 0;
        }
        else
        {
          if (line_text[i] =='\\')
          {
            i++;
            if (i == text_size) break;
          }
        }
      }
      // Out of String
      else
      {
        // Open String
        if (line_text[i] == '"')
        {
          in_string = 1;
        }
        else
        {
          if (line_text[i] == '(')
          {
            leftp_cnt++;
          }
          else if (line_text[i] == ')')
          {
            rightp_cnt++;
          }
        }
      }
    }

    s_text += line_text;
    if (in_string == 0)
    {
      s_text += " ";
    }
  } while ((leftp_cnt > rightp_cnt) || (in_string != 0));

  // これは後で
  // #'(...)
  //  s_text = expand_function( s_text );
  //
  // 'ABC '(...)
  //  s_text = expand_quote( s_text );

  return s_text;
}

string expand_function(string str)
{
  string line_text;
  int leftp_cnt = 0;
  int rightp_cnt = 0;
  int text_size;
  int in_string = 0;
  int in_function = 0;
  int function_cnt = 0;
  int function_stack[20];
  int sp = 0;

  line_text = str;
  text_size = line_text.size();

  for (int i = 0; i < text_size; i++)
  {
    // In String
    if (in_string != 0)
    {
      // Close String
      if (line_text[i] == '"')
      {
        in_string = 0;
      }
      else
      {
        if (line_text[i] =='\\')
        {
          i++;
          if (i == text_size) break;
        }
      }
    }
    // Out of String
    else
    {
      // Open String
      if (line_text[i] == '"')
      {
        in_string = 1;
      }
      else
      {
        if (line_text[i] == '(')
        {
          leftp_cnt++;
        }
        else if (line_text[i] == ')')
        {
          rightp_cnt++;

          if ((in_function > 0) && ((leftp_cnt - rightp_cnt) == function_cnt))
          {
            line_text.insert(i + 1, ")");
            text_size += 1;
            i += 1;
            in_function--;
            // Restore old quote_cnt
            function_cnt = function_stack[sp--];
          }
        }
        // for #'... -> (function ... ) expand
        else if (line_text[i] == '#')
        {
          if (((i + 1) < text_size) && (line_text[i + 1] == '\''))
          {
            line_text.erase(i, 2);
            line_text.insert(i, "(function ");
            text_size += 9;
            i += 9;
            in_function++;
            // Save old quote_cnt
            function_stack[++sp] = function_cnt;
            function_cnt = (leftp_cnt - rightp_cnt);

            // for ... == atom case
            if (line_text[i + 1] != '(')
            {
              // skip one atom
              i++;
              for ( ; i < text_size; i++)
              {
                // Detect separator
                if ((line_text[i] == '(') ||
                   (line_text[i] == ')') ||
                   (line_text[i] == ' '))
                {
                  line_text.insert(i, ")");
                  text_size += 1;
                  in_function--;
                  // Restore old quote_cnt
                  function_cnt = function_stack[sp--];
                  break;
                }
              }
            }
          }
        }
      }
    }
  }

  return line_text;
}

string expand_quote(string str)
{
  string line_text;
  int leftp_cnt = 0;
  int rightp_cnt = 0;
  int text_size;
  int in_string = 0;
  int in_quote = 0;
  int quote_cnt = 0;
  int quote_n = 0;
  int quote_stack[20][2];     // [0]:quote_cnt [1]:quote_n 
  int sp = 0;

  line_text = str;
  text_size = line_text.size();

  for (int i = 0; i < text_size; i++)
  {
    // In String
    if (in_string != 0)
    {
      // Close String
      if (line_text[i] == '"')
      {
        in_string = 0;
      }
      else
      {
        if (line_text[i] =='\\')
        {
          i++;
          if (i == text_size) break;
        }
      }
    }
    // Out of String
    else
    {
      // Open String
      if (line_text[i] == '"')
      {
        in_string = 1;
      }
      else
      {
        if (line_text[i] == '(')
        {
          leftp_cnt++;
        }
        else if (line_text[i] == ')')
        {
          rightp_cnt++;

          if ((in_quote > 0) && ((leftp_cnt - rightp_cnt) == quote_cnt))
          {
            for (int j = 0; j < quote_n; j++)
            {
              line_text.insert(i + 1, ")");
              text_size += 1;
              i += 1;
              in_quote--;
            }
            // Restore old quote_cnt
            quote_cnt = quote_stack[sp][0];
            quote_n = quote_stack[sp--][1];
          }
        }
        // '... -> (quote ... ) expand
        else if (line_text[i] == '\'')
        {
          // Save old quote_cnt
          quote_stack[++sp][0] = quote_cnt;
          quote_stack[sp][1] = quote_n;

          line_text.erase(i, 1);
          line_text.insert(i, "(quote ");
          text_size += 6;
          i += 6;
          in_quote++;
          quote_n = 1;

          i++;
          for ( ; i < text_size; i++)
          {
            if (line_text[i] == ' ') {
              // no operation
            } else if (line_text[i] == '\'') {
              line_text.erase(i, 1);
              line_text.insert(i, "(quote ");
              text_size += 6;
              i += 6;
              in_quote++;
              quote_n++;
            } else {
              break;
            }
          }

          quote_cnt = (leftp_cnt - rightp_cnt);

          // '( case
          if (line_text[i] == '(')
          {
            i--;
          // 'atom case
          } else {
            // skip one atom
            i++;
            for ( ; i < text_size; i++)
            {
              // Detect separator
              if ((line_text[i] == '(') ||
                 (line_text[i] == ')') ||
                 (line_text[i] == ' '))
              {
                for (int j = 0; j < quote_n; j++)
                {
                  line_text.insert(i, ")");
                  text_size += 1;
                  i++;
                  in_quote--;
                }

                i--;
                // Restore old quote_cnt
                quote_cnt = quote_stack[sp][0];
                quote_n = quote_stack[sp--][1];
                break;
              }
            }
          }
        }
      }
    }
  }

  return line_text;
}

bool is_dot(string s)
{
  char c = s[0];
  int length = s.size();

  if ((length == 1) && (c == '.'))
  {
    return true;
  }
  else
  {
    return false;
  }
}


bool is_int(string s)
{
  char c;
  int end = s.size();
  bool flag = true;

  for (int i = 0; i < end; i++)
  {
    c = s[i];
    if (((c >= '0') && (c <= '9')) ||
        (c == '+') ||
        (c == '-'))
    {
      continue;
    }
    flag = false;
    break;
  }
  return flag;
}


bool is_float(string s)
{
  char c;
  int end = s.size();
  bool flag = true;

  for (int i = 0; i < end; i++)
  {
    c = s[i];
    if (((c >= '0') && (c <= '9')) ||
        (c == '.') ||
        (c == '+') ||
        (c == '-') ||
        (c == 'e'))
    {
      continue;
    }
    flag = false;
    break;
  }
  return flag;
}


void error_exit(string str)
{
  cout << str << endl;
  exit(1);
}


// abc                             (Atom) *
// 123 -123                        (Int) *
// 1.23 -1.23 1.23e10 -1.23e-10    (Float) *
// "ABC"                           (String) *
// (...)                           (List) *
// 'ABC '(...)                     (quote ...) -
// #(1 2 3)                        (Vector) *
// #'(...)                         (function () (...)) -

string get_elem(string text, int *idx, Type *type)
{
  int i;
  int i_start;
  int end;
  char c;
  string s;

  end = text.size();

  // Skip space
  for (i = *idx; i < end; i++)
  {
    c = text[i];
    if (c != ' ') break;
  }
  *idx = i;

  // End of text
  if (i == end)
  {
    *type = Type::Null;
    return "";
  }

  *idx = i + 1;

  // is Parenthesis
  if (c == '(')
  {
    *type = Type::L_Parent;
    return "(";
  }
  if (c == ')')
  {
    *type = Type::R_Parent;
    return ")";
  }

  // is Vector
  if (c == '#')
  {
    i++;
    if (i == end)
    {
      *type = Type::Atom;
      return "#";
    }

    c = text[i];

    *idx = i + 1;

    if (c == '(')
    {
      *type = Type::V_Parent;
      return "#(";
    }
  }

  // is String
  if (c == '"')
  {
    i_start = i;
    for (i++; i < end; i++)
    {
      c = text[i];
      if (c == '\\')
      {
        i++;
      }
      else
      {
        if (c == '"') break;
      }
    }

    *idx = i + 1;

    *type = Type::String;
    return text.substr(i_start + 1, i - i_start - 1);
  }

  // is Atom or Num_Int or Num_Float or Dot
  i_start = i;
  for (i++; i < end; i++)
  {
    c = text[i];
    if (c == ' ') break;
    if (c == '(') break;
    if (c == ')') break;
  }

  *idx = i;

  s = text.substr(i_start, i - i_start);

  // Dot
  if (is_dot(s) == true)
  {
    *type = Type::Dot;
  }
  // Int
  else if (is_int(s) == true)
  {
    try
    {
      long l = stol(s);
      *type = Type::Num_Int;
    }
    catch(const std::exception& e)
    {
      *type = Type::Atom;
    }
  }
  // Float
  else if (is_float(s) == true)
  {
    try
    {
      double d = stod(s);
      *type = Type::Num_Float;
    }
    catch(const std::exception& e)
    {
      *type = Type::Atom;
    }
  }
  // Atom
  else
  {
    *type = Type::Atom;
  }
  return s;
}


int count_items(vector<Token> *tokens, int idx, int i)
{
  string s;
  int rest_idx;
  int car_rest_idx, cdr_rest_idx;
  Type type;
  Object *p_car, *p_cdr;

  s = (*tokens)[idx].str;
  type = (*tokens)[idx].type;

  rest_idx = idx + 1;

//  cout << "[count_i s] " << s << endl;
//  cout << "[count_i t] " << (int)type << endl;

  // (
  if (type == Type::L_Parent)
  {
    p_car = s_read(tokens, rest_idx, &car_rest_idx);

    p_cdr = s_cdr_read(tokens, car_rest_idx, &cdr_rest_idx);

    return count_items(tokens, cdr_rest_idx, i + 1);
  }

  // )
  else if (type == Type::R_Parent)
  {
    // End of Vector
    return i;
  }

  // #(
  else if (type == Type::V_Parent)
  {
    // in new Vector
    p_car = s_read(tokens, rest_idx, &car_rest_idx);
    
    v_rest_skip(tokens, car_rest_idx, &cdr_rest_idx);

    return count_items(tokens, cdr_rest_idx, i + 1);
  }

  // String
  else if (type == Type::String)
  {
    return count_items(tokens, rest_idx, i + 1);
  }

  // Number_int
  else if (type == Type::Num_Int)
  {
    return count_items(tokens, rest_idx, i + 1);
  }
  // Number_float
  else if (type == Type::Num_Float)
  {
    return count_items(tokens, rest_idx, i + 1);
  }

  // Atom
  else if (type == Type::Atom)
  {
    return count_items(tokens, rest_idx, i + 1);
  }

  // Illegal form
  else
  {
    error_exit("Illegal form detected! in count_items()");
    return 0;
  }
}


// --------------- Read One S-Expression ---------------


void get_elems(string text, vector<Token> *tokens)
{
  string s;
  string rest;
  int idx = 0;
  Type type;
  Token *tp;

  do
  {
    s = get_elem(text, &idx , &type);
    rest = text.substr(idx);
    if (s == "") return;
    tp = new Token();
    tp->str = s;
    tp->type = type;
    (*tokens).push_back(*tp);
  } while (rest != "");
}


Object *s_read(vector<Token> *tokens, int idx, int *rest_idx)
{
  string s;
  int car_rest_idx, cdr_rest_idx;
  int n;
  Type type;
  Object *p;
  Object *p_car;

  s = (*tokens)[idx].str;
  type = (*tokens)[idx].type;

  *rest_idx = idx + 1;

  cout << "[s] " << s << endl;
//  cout << "[t] " << (int)type << endl;

  // (
  if (type == Type::L_Parent)
  {
    p = s_cdr_read(tokens, *rest_idx, &cdr_rest_idx);

    *rest_idx = cdr_rest_idx;

    return p;
  }

  // )
  else if (type == Type::R_Parent)
  {
    error_exit("Illegal \")\" detected! in s_read()");
    return NULL;
  }

  // #(
  else if (type == Type::V_Parent)
  {
    n = count_items(tokens, *rest_idx, 0);

    cout << "[n] " << n << endl;

    p = new Vector((long)n);
    p_car = s_read(tokens, *rest_idx, &car_rest_idx);

    p->set_value(0, p_car);
    v_rest_read(p, 1, tokens, car_rest_idx, &cdr_rest_idx);

    *rest_idx = cdr_rest_idx;

    return p;
  }

  // String
  else if (type == Type::String)
  {
    p = new String;
    p->set_value(s);
    return p;
  }

  // Number_int
  else if (type == Type::Num_Int)
  {
    p = new Num_int;
    p->set_value(stol(s));
    return p;
  }

  // Number_float
  else if (type == Type::Num_Float)
  {
    p = new Num_float;
    p->set_value(stod(s));
    return p;
  }

  // Atom
  else if (type == Type::Atom)
  {
    p = mp->get_atom(s);
    return p;
  }

  // Illegal form
  else
  {
    error_exit("Illegal form detected! in s_read()");
    return NULL;
  }
}


Object *s_cdr_read(vector<Token> *tokens, int idx, int *rest_idx)
{
  string s;
  int car_rest_idx, cdr_rest_idx, cdr2_rest_idx;
  int n;
  Type type;
  Object *p, *q;
  Object *p_car, *p_cdr;
  Object *q_car, *q_cdr;

  s = (*tokens)[idx].str;
  type = (*tokens)[idx].type;

  *rest_idx = idx + 1;

  cout << "[cdr s] " << s << endl;
//  cout << "[cdr t] " << (int)type << endl;

  // .
  if (type == Type::Dot)
  {
    p = s_read(tokens, *rest_idx, &car_rest_idx);

    // skip one )
    s = (*tokens)[car_rest_idx].str;
    type = (*tokens)[car_rest_idx].type;

    *rest_idx = car_rest_idx + 1;

    if (type == Type::R_Parent)
    {
      return p;
    }
    else
    {
      error_exit("Illegal Dot form detected! in s_cdr_read()");
      return NULL;
    }
  }

  // (
  else if (type == Type::L_Parent)
  {
    p = new Cell;

    p_car = s_cdr_read(tokens, *rest_idx, &cdr_rest_idx);

    p->set_car(p_car);
    p_cdr = s_cdr_read(tokens, cdr_rest_idx, &cdr2_rest_idx);

    p->set_cdr(p_cdr);
    *rest_idx = cdr2_rest_idx;

    return p;
  }

  // )
  else if (type == Type::R_Parent)
  {
    p = mp->get_atom("nil");
    return p;
  }

  // #(
  else if (type == Type::V_Parent)
  {
    p = new Cell;

    // in new Vector
    n = count_items(tokens, *rest_idx, 0);

    cout << "[cdr n] " << n << endl;

    q = new Vector((long)n);
    q_car = s_read(tokens, *rest_idx, &car_rest_idx);

    q->set_value(0, q_car);
    v_rest_read(q, 1, tokens, car_rest_idx, &cdr_rest_idx);

    p->set_car(q);
    p_cdr = s_cdr_read(tokens, cdr_rest_idx, &cdr2_rest_idx);

    p->set_cdr(p_cdr);
    *rest_idx = cdr2_rest_idx;

    return p;
  }

  // String
  else if (type == Type::String)
  {
    p = new Cell;

    p_car = new String;
    p_car->set_value(s);

    p->set_car(p_car);
    p_cdr = s_cdr_read(tokens, *rest_idx, &cdr_rest_idx);

    p->set_cdr(p_cdr);
    *rest_idx = cdr_rest_idx;

    return p;
  }

  // Number_int
  else if (type == Type::Num_Int)
  {
    p = new Cell;

    p_car = new Num_int;
    p_car->set_value(stol(s));

    p->set_car(p_car);
    p_cdr = s_cdr_read(tokens, *rest_idx, &cdr_rest_idx);

    p->set_cdr(p_cdr);
    *rest_idx = cdr_rest_idx;

    return p;
  }

  // Number_float
  else if (type == Type::Num_Float)
  {
    p = new Cell;

    p_car = new Num_float;
    p_car->set_value(stod(s));

    p->set_car(p_car);
    p_cdr = s_cdr_read(tokens, *rest_idx, &cdr_rest_idx);

    p->set_cdr(p_cdr);
    *rest_idx = cdr_rest_idx;

    return p;
  }

  // Atom
  else if (type == Type::Atom)
  {
    p = new Cell;

    p_car = mp->get_atom(s);
    p->set_car(p_car);
    p_cdr = s_cdr_read(tokens, *rest_idx, &cdr_rest_idx);

    p->set_cdr(p_cdr);
    *rest_idx = cdr_rest_idx;

    return p;
  }

  // Illegal form
  else
  {
    error_exit("Illegal form detected! in s_cdr_read()");
    return NULL;
  }
}


void v_rest_read(Object *v, int i, vector<Token> *tokens, int idx, int *rest_idx)
{
  string s;
  int car_rest_idx, cdr_rest_idx, cdr2_rest_idx;

  int n;
  Type type;
  Object *p;
  Object *p_car, *p_cdr;

  s = (*tokens)[idx].str;
  type = (*tokens)[idx].type;

  *rest_idx = idx + 1;

  cout << "[v_rest s] " << s << endl;
//  cout << "[v_rest t] " << (int)type << endl;

  // (
  if (type == Type::L_Parent)
  {
    // in Car
    p = new Cell;
    p_car = s_read(tokens, *rest_idx, &car_rest_idx);

    p->set_car(p_car);
    p_cdr = s_cdr_read(tokens, car_rest_idx, &cdr_rest_idx);
    
    p->set_cdr(p_cdr);
    v->set_value(i, p);
    v_rest_read(v, i + 1, tokens, cdr_rest_idx, &cdr2_rest_idx);

    *rest_idx = cdr2_rest_idx;
  }

  // )
  else if (type == Type::R_Parent)
  {
    // End of Vector
  }

  // #(
  else if (type == Type::V_Parent)
  {
    // in new Vector
    n = count_items(tokens, *rest_idx, 0);

    cout << "[v_rest n] " << n << endl;

    p = new Vector((long)n);
    p_car = s_read(tokens, *rest_idx, &car_rest_idx);

    p->set_value(0, p_car);
    v_rest_read(p, 1, tokens, car_rest_idx, &cdr_rest_idx);

    v->set_value(i, p);
    v_rest_read(v, i + 1, tokens, cdr_rest_idx, &cdr2_rest_idx);

    *rest_idx = cdr2_rest_idx;
  }

  // String
  else if (type == Type::String)
  {
    p = new String;
    p->set_value(s);
    v->set_value(i, p);
    v_rest_read(v, i + 1, tokens, *rest_idx, &cdr_rest_idx);

    *rest_idx = cdr_rest_idx;
  }

  // Number_int
  else if (type == Type::Num_Int)
  {
    p = new Num_int;
    p->set_value(stol(s));	// Conv error may occur

    v->set_value(i, p);
    v_rest_read(v, i + 1, tokens, *rest_idx, &cdr_rest_idx);

    *rest_idx = cdr_rest_idx;
  }

  // Number_float
  else if (type == Type::Num_Float)
  {
    p = new Num_float;
    p->set_value(stod(s));	// Conv error may occur

    v->set_value(i, p);
    v_rest_read(v, i + 1, tokens, *rest_idx, &cdr_rest_idx);

    *rest_idx = cdr_rest_idx;
  }

  // Atom
  else if (type == Type::Atom)
  {
    p = mp->get_atom(s);
    v->set_value(i, p);
    v_rest_read(v, i + 1, tokens, *rest_idx, &cdr_rest_idx);

    *rest_idx = cdr_rest_idx;
  }

  // Illegal form
  else
  {
    error_exit("Illegal form detected! in v_rest_read()");
  }
}


void v_rest_skip(vector<Token> *tokens, int idx, int *rest_idx)
{
  string s;
  int car_rest_idx, cdr_rest_idx, cdr2_rest_idx;

  Type type;
  Object *p;
  Object *p_car, *p_cdr;

  s = (*tokens)[idx].str;
  type = (*tokens)[idx].type;

  *rest_idx = idx + 1;

//  cout << "[v_rest_skip s] " << s << endl;
//  cout << "[v_rest_skip t] " << (int)type << endl;

  // (
  if (type == Type::L_Parent)
  {
    // in Car
    p_car = s_read(tokens, *rest_idx, &car_rest_idx);

    p_cdr = s_cdr_read(tokens, car_rest_idx, &cdr_rest_idx);

    v_rest_skip(tokens, cdr_rest_idx, &cdr2_rest_idx);

    *rest_idx = cdr2_rest_idx;
  }

  // )
  else if (type == Type::R_Parent)
  {
    // End of Vector
  }

  // #(
  else if (type == Type::V_Parent)
  {
    p_car = s_read(tokens, *rest_idx, &car_rest_idx);

    v_rest_skip(tokens, car_rest_idx, &cdr_rest_idx);

    v_rest_skip(tokens, cdr_rest_idx, &cdr2_rest_idx);

    *rest_idx = cdr2_rest_idx;
  }

  // String
  else if (type == Type::String)
  {
    v_rest_skip(tokens, *rest_idx, &cdr_rest_idx);

    *rest_idx = cdr_rest_idx;
  }

  // Number_int
  else if (type == Type::Num_Int)
  {
    v_rest_skip(tokens, *rest_idx, &cdr_rest_idx);

    *rest_idx = cdr_rest_idx;
  }

  // Number_float
  else if (type == Type::Num_Float)
  {
    v_rest_skip(tokens, *rest_idx, &cdr_rest_idx);

    *rest_idx = cdr_rest_idx;
  }

  // Atom
  else if (type == Type::Atom)
  {
    v_rest_skip(tokens, *rest_idx, &cdr_rest_idx);

    *rest_idx = cdr_rest_idx;
  }

  // Illegal form
  else
  {
    error_exit("Illegal form detected! in v_rest_skip()");
  }
}


bool is_space(string str)
{
  for (int i = 0; i < str.size(); i++)
  {
    if (str[i] != ' ')
    {
      return false;
    }
  }
  return true;
}


// --------------- Lisp basic functions ---------------

Atom *atom(Object *p)
{
  if (typeid(*p) == id_Atom)
  {
    return p_t;
  }
  else
  {
    return p_nil;
  }
}

Atom *atom2(Object *p)
{
  if ((typeid(*p) == id_String) ||
      (typeid(*p) == id_Num_int) ||
      (typeid(*p) == id_Num_float) ||
      (typeid(*p) == id_Vector))
  {
    return p_t;
  }
  else
  {
    return p_nil;
  }
}

Atom *eq(Object *p, Object *q)
{
  if (typeid(*p) == typeid(*q))
  {
    if (p == q)
    {
      return p_t;
    }
    else
    {
      return p_nil;
    }
  }
  else
  {
    return p_nil;
  }
}

Object *car(Object *p)
{
  if (typeid(*p) == id_Cell)
  {
    if (((Cell*)p)->car != NULL)
    {
      return ((Cell*)p)->car;
    }
    else
    {
      return p_nil;
    }
  }
  else
  {
    return p_nil;
  }
}

Object *cdr(Object *p)
{
  if (typeid(*p) == id_Cell)
  {
    if (((Cell*)p)->cdr != NULL)
    {
      return ((Cell*)p)->cdr;
    }
    else
    {
      return p_nil;
    }
  }
  else
  {
    return p_nil;
  }
}

Cell *cons(Object *p, Object *q)
{
  return new Cell(p, q);
}


// --------------- Lisp additional functions ---------------

Object *caar(Object *p)
{
  return car(car(p) );
}

Object *cadr(Object *p)
{
  return car(cdr(p));
}

Object *cadar(Object *p)
{
  return car(cdr(car(p)));
}

Object *caddr(Object *p)
{
  return car(cdr(cdr(p)));
}

Object *caddar(Object *p)
{
  return car(cdr(cdr(car(p))));
}

Cell *list(Object *p, Object *q)
{
  return cons(p, cons(q, p_nil));
}

Atom *null(Object *p)
{
  return eq(p, p_nil);
}

Atom *s_and(Object *x, Object *y)
{
  if (x != p_nil)
  {
    if (y != p_nil)
    {
      return p_t;
    }
    else
    {
      return p_nil;
    }
  }
  else
  {
    return p_nil;
  }
}

Atom *s_not(Object *x)
{
  if (x != p_nil)
  {
    return p_nil;
  }
  else
  {
    return p_t;
  }
}

Object *append(Object *x, Object *y)
{
  if (null(x) == p_t)
  {
    return y;
  }
  else
  {
    return cons(car(x), append(cdr(x), y));
  }
}

Object *s_pair(Object *x, Object *y)
{
  if (s_and(null(x), null(y)) == p_t)
  {
    return p_nil;
  }
  else if (s_and(s_not(atom(x)), s_not(atom(y))) == p_t)
  {
    return cons(list(car(x), car(y)), s_pair(cdr(x), cdr(y)));
  }
  else
  {
    return p_nil;
  }
}

Object *assoc(Object *x, Object *y)
{
  if (y == p_nil)
  {
    return p_nil;
  }
  else if (eq(caar(y), x) == p_t)
  {
    return cadar(y);
  }
  else
  {
    return assoc(x, cdr(y));
  }
}

Object *evcon(Object *c, Object *a)
{
  if (s_eval(caar(c), a) != p_nil)
  {
    return s_eval(cadar(c), a);
  }
  else
  {
    return evcon(cdr(c), a);
  }
}

Object *evlis(Object *m, Object *a)
{
  if (null(m) == p_t)
  {
    return p_nil;
  }
  else
  {
    return cons(s_eval(car(m), a), evlis(cdr(m), a));
  }
}

Object *s_eval(Object *e, Object *a)
{
  if (atom2(e) == p_t)
  {
    return e;             // Constants
  }
  else if (atom(e) == p_t)
  {
    if ((e == p_t ) || (e == p_nil))
    {
      return e;
    }

    return assoc(e, a);
  }
  else if (atom2(car(e)) == p_t)
  {
    return e;             // Constants List
  }
  else if (atom(car(e)) == p_t)
  {
    if (car(e) == p_quote)
    {
      return cadr(e);
    }
    else if (car(e) == p_atom)
    {
      return atom(s_eval(cadr(e), a));
    }
    else if (car(e) == p_eq)
    {
      return eq(s_eval(cadr(e), a), s_eval(caddr(e), a));
    }
    else if (car(e) == p_null)
    {
      return null(s_eval(cadr(e), a));                            // (null
    }
    else if (car(e) == p_not)
    {
      return s_not(s_eval(cadr(e), a));                           // (not
    }
    else if (car(e) == p_car)
    {
      return car(s_eval(cadr(e), a));
    }
    else if (car(e) == p_cdr)
    {
      return cdr(s_eval(cadr(e), a));
    }
    else if (car(e) == p_cons)
    {
      return cons(s_eval(cadr(e), a), s_eval(caddr(e), a));
    }
    else if (car(e) == p_append)
    {
      return append(s_eval(cadr(e), a), s_eval(caddr(e), a));     // (append
    }
    else if (car(e) == p_cond)
    {
      return evcon(cdr(e), a);
    }
    else
    {
      return s_eval(cons(assoc(car(e), a), cdr(e)), a);           // Named Functions
    }
  }
  else if (caar(e) == p_label)
  {
    return s_eval(cons(caddar(e), cdr(e)), cons(list(cadar(e), car(e)), a));
  }
  else if (caar(e) == p_lambda)
  {
    return s_eval(caddar(e), append(s_pair(cadar(e), evlis(cdr(e), a)), a));
  }
  else
  {
    return p_nil;
  }
}


// --------------- Main Loop ---------------

int main()
{
  string str;
  vector<Token> tokens;
  int rst_idx;
  Object *p;
  Object *q;

  while (1)
  {
    str = s_input();

    // Expand #' '
    str = expand_function(str);
    str = expand_quote(str);

    tokens.clear();
    get_elems(str, &tokens);

//    for (int i=0; i<tokens.size(); i++)
//    {
//      cout << tokens[i].str << " " << (int)(tokens[i].type) <<endl;
//    }

    if (is_space(str) == false)
    {
      // Input String
      cout << "[str] " << str << endl;

      // read
      p = s_read(&tokens, 0, &rst_idx);

      // print
      cout << "[exp] ";
      p->print();
      cout << endl;

      // eval
      // a = ((aaa bbb)) for Test
      q = s_eval(p, cons(cons(p_aaa, cons(p_bbb, p_nil)), p_nil));

      // print
      cout << "[eval] ";
      q->print();
      cout << endl;

      // All Atoms
      mp->print_all();

      // Clean Objects
      // Input Exp
      if (p->ref_cnt == 0)
      {
        cout << "Delete Object [Class ID]= " << typeid(*p).name() << endl;
        delete p;
      }

      // Output Exp
      if (q->ref_cnt == 0)
      {
        cout << "Delete Object [Class ID]= " << typeid(*q).name() << endl;
        delete q;
      }

    }
  }

  return 0;
}

//
// get_elem() が何度も呼ばれるのは効率が悪いので、
// get_elems() 関数で、一気に string -> token 変換することにする。
//


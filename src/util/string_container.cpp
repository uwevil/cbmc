/*******************************************************************\

Module: Container for C-Strings

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#include <cstring>

#include "string_container.h"

string_containert string_container;

/*******************************************************************\

Function: string_ptrt::string_ptrt

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

string_ptrt::string_ptrt(const char *_s):s(_s), len(strlen(_s))
{
}

/*******************************************************************\

Function: string_ptrt::operator==

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

bool string_ptrt::operator==(const string_ptrt &other) const
{
  if(len!=other.len)
    return false;

  return len==0 || memcmp(s, other.s, len)==0;
}

/*******************************************************************\

Function: string_containert::string_containert

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void initialize_string_container();

string_containert::string_containert()
{
  // pre-allocate empty string -- this gets index 0
  get("");

  // allocate strings
  initialize_string_container();
}

/*******************************************************************\

Function: string_containert::~string_containert

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

string_containert::~string_containert()
{
}

/*******************************************************************\

Function: string_containert::get

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

unsigned string_containert::get(const char *s)
{
  string_ptrt string_ptr(s);

  hash_tablet::iterator it=hash_table.find(string_ptr);

  if(it!=hash_table.end())
    return it->second;

  size_t r=hash_table.size();

  // these are stable
  string_list.push_back(std::string(s));
  string_ptrt result(string_list.back());

  hash_table[result]=r;

  // these are not
  string_vector.push_back(&string_list.back());

  return r;
}

/*******************************************************************\

Function: string_containert::get

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

unsigned string_containert::get(const std::string &s)
{
  string_ptrt string_ptr(s);

  hash_tablet::iterator it=hash_table.find(string_ptr);

  if(it!=hash_table.end())
    return it->second;

  size_t r=hash_table.size();

  // these are stable
  string_list.push_back(s);
  string_ptrt result(string_list.back());

  hash_table[result]=r;

  // these are not
  string_vector.push_back(&string_list.back());

  return r;
}

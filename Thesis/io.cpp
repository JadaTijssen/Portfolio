#include "tropnum.h"
// I/O: these are never a class member
// Input:
std::istream& operator>> (std::istream& in, TropicalNumber& tnum)
{
  std::string word;
  in >> word;
  if (word.compare("Inf")==0)
  {
    tnum.value = DBL_MAX;
  } else
  {
    tnum.value = std::stod(word);
  }
  tnum.initialized = true;
  return in;
}

// Output:
std::ostream& operator<< (std::ostream& out, const TropicalNumber& tnum)
{
  if (!tnum.initialized)
  {
    out << "Undefined";
  } else
  {
    if (tnum.value == DBL_MAX)
    {
      out << "Inf";
    } else
    {
      out << tnum.value;
    }
  }
  return out;
}

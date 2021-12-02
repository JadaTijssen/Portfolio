#ifndef TROPNUM
#define TROPNUM

#include <iostream>
#include <float.h>

class TropicalNumber
{
private:
  bool initialized;
  double value;
public:
  // Constructors.
  TropicalNumber () 
  {
    initialized = false;
  };
  
  TropicalNumber (double initialValue) 
  {
    initialized = true;
    value = initialValue;
  };
  
  // Copy constructor.
  TropicalNumber (const TropicalNumber& rhs)
  {
    if (!rhs.initialized)
    {
      std::cerr << "\nWarning: unitialized Tropical number used in the Copy Constructor.\n";
    }
    initialized = rhs.initialized;
    value = rhs.value;
  }
  
  // Destructor
  virtual ~TropicalNumber ()
  {
    // This class does not use any dynamic memory,
    // so the destructor does not have to deallocate
    // any. Hence, it is simply empty.
  };
  
  // Operators.
  // comparison for less than (<)
  bool operator< (const TropicalNumber& rhs)
  {
    return value < rhs.value;
  }
  
  // comparison for less than or equal (<=)
  bool operator<= (const TropicalNumber& rhs)
  {
    return value <= rhs.value;
  }
  
  // comparison for equality (==)
  bool operator== (const TropicalNumber& rhs)
  {
    return value == rhs.value;
  }

  // comparison for inequality (!=)
  bool operator!= (const TropicalNumber& rhs)
  {
    return value != rhs.value;
  }

  // comparison for greater than (>)
  bool operator> (const TropicalNumber& rhs)
  {
    return value > rhs.value;
  }
  
  // comparison for less than or equal (>=)
  bool operator>= (const TropicalNumber& rhs)
  {
    return value >= rhs.value;
  }
  
  // Assignment operator.
  TropicalNumber& operator= (const TropicalNumber& rhs)
  {
    if (this != &rhs) // Don't copy to self 
      {
  if (!rhs.initialized)
  {
    std::cerr << "\nWarning: unitialized Tropical number in right hand side of an assignment.\n";
  }
  initialized = rhs.initialized;
  value = rhs.value;
      }
    return *this;
  }
  
  // Address of operator (non const): example of usage:  TropicalNumber *c1 = &c2;
  TropicalNumber* operator& ()
  {
    return (this);
  }
  
  // Address of operator (const): example of usage:  const TropicalNumber *c1 = &c2;
  const TropicalNumber* operator& () const
  {
    return (this);
  }
  
  // Overloaded operators:
  // += operator (a+=b is now a=min(a,b))
  TropicalNumber operator+=(const TropicalNumber& rhs)
  {
    if (!(initialized && rhs.initialized))
    {
      std::cerr << "\nWarning: unitialized argument used in + operator.\n";
    }
    initialized = initialized && rhs.initialized;
    if (rhs.value < this->value)
    {
      this->value = rhs.value;
    }
    return *this; // return the result by reference
  }

  friend TropicalNumber operator+(TropicalNumber lhs, const TropicalNumber& rhs)
  {    
    lhs += rhs; // reuse += operator
    return lhs; // return the result by value (uses move constructor)
  }

  // *= operator (a*=b is now a=a+b
  TropicalNumber operator*=(const TropicalNumber& rhs)
  {
    if (!(initialized && rhs.initialized))
    {
      std::cerr << "\nWarning: unitialized argument used in * operator.\n";
    }
    initialized = initialized && rhs.initialized;
    this->value += rhs.value;
    return *this; // return the result by reference
  }

  friend TropicalNumber operator*(TropicalNumber lhs, const TropicalNumber& rhs)
  {    
    lhs *= rhs; // reuse *= operator
    return lhs; // return the result by value (uses move constructor)
  }
  
  friend std::ostream& operator<<(std::ostream& out, const TropicalNumber& tnum);
  friend std::istream& operator>>(std::istream& in, TropicalNumber& tnum);

  // Misc. functions
  void setInf()
  {
    initialized = true;
    value = DBL_MAX;
  }

  bool isInf()
  {
    return (value == DBL_MAX);
  }
};
  
#endif

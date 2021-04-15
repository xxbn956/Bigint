// $Id: bigint.cpp,v 1.4 2021-04-14 13:24:23-07 - - $

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "bigint.h"

bigint::bigint (long that): uvalue (that), is_negative (that < 0) {
   DEBUGF ('~', this << " -> " << uvalue)
}

bigint::bigint (const ubigint& uvalue_, bool is_negative_):
                uvalue(uvalue_), is_negative(is_negative_) {
}

bigint::bigint (const string& that) {
   is_negative = that.size() > 0 and that[0] == '_';
   uvalue = ubigint (that.substr (is_negative ? 1 : 0));
}

bigint bigint::operator+ () const {
   return *this;
}

bigint bigint::operator- () const {
   return {uvalue, not is_negative};
}

bigint bigint::operator+ (const bigint& that) const {
   ubigint result;
   bool b;
   bigint larger;
   if (is_negative && that.is_negative)
   {
     result = uvalue + that.uvalue;
     return {result,true};
   }
   else if (is_negative)
   {
     result = (uvalue > that.uvalue) ?
              uvalue - that.uvalue : that.uvalue - uvalue;
     b = (uvalue > that.uvalue) ? true : false;
     return {result,b};
   }
   else if (that.is_negative)
   {
     result = (that.uvalue > uvalue) ?
              that.uvalue - uvalue : uvalue - that.uvalue;
     b = (that.uvalue > uvalue) ? true : false;
     return {result,b};
   }
   else
   {
     result = uvalue + that.uvalue;
     return result;
   }
   /*
   if (!(is_negative != that.is_negative))
   {
     result = uvalue + that.uvalue;
     b = is_negative;
   }
   else 
   {
     if (uvalue == that.uvalue)
     {
       result = uvalue - that.uvalue;
       b = false;
     }
     else if (uvalue > that.uvalue)
     {
       result = uvalue - that.uvalue;
       b = is_negative;
     }
     else
     {
       result = that.uvalue - uvalue;
       b = that.is_negative;
     }
   }
   return {result, b};
   */
}

bigint bigint::operator- (const bigint& that) const {
  bigint result;
  if(is_negative != that.is_negative) {
    result = uvalue + that.uvalue;
    result.is_negative = (is_negative) ? true:false;
  } else {
    if(uvalue > that.uvalue) {
      result = uvalue - that.uvalue;
      result.is_negative = false;
    } else {
      result = that.uvalue - uvalue;
      result.is_negative = true;
    }
    if(uvalue == that.uvalue) {
      result.is_negative = false;
    }
  }
  return result;
}


bigint bigint::operator* (const bigint& that) const {
  bigint result = uvalue * that.uvalue;
  result.is_negative = (is_negative == that.is_negative) ? false:true;
  return result;
}

bigint bigint::operator/ (const bigint& that) const {
  bigint result = uvalue / that.uvalue;
  result.is_negative = (is_negative == that.is_negative) ? false:true;
  return result;
}

bigint bigint::operator% (const bigint& that) const {
  bigint result = uvalue % that.uvalue;
  return result;
}

bool bigint::operator== (const bigint& that) const {
   return is_negative == that.is_negative and uvalue == that.uvalue;
}

bool bigint::operator< (const bigint& that) const {
   if (is_negative != that.is_negative) return is_negative;
   return is_negative ? uvalue > that.uvalue
                      : uvalue < that.uvalue;
}

ostream& operator<< (ostream& out, const bigint& that) {
   if(that.is_negative) {
     return out << "-" << that.uvalue;
   } else {
     return out << that.uvalue;
   }
}


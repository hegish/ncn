#include <cmath>
#include <limits>
#include <type_traits>
#include <algorithm>

#include "almost_equal.h"

using namespace std;

template<typename T> bool almost_equal(T x, T y, int ulp)
{
   // the IEEE standard says that any comparison operation involving a NAN must return false
   if( isnan(x) || isnan(y) )
      return false;
   
   if( abs(x-y) <= abs(numeric_limits<T>::epsilon()*x+numeric_limits<T>::epsilon()*y) * ulp )
      return true;
   
   return abs(x-y) < numeric_limits<T>::min(); // see if result is subnormal
}
// explicitly create template definitions
template bool almost_equal(float x, float y, int ulp);
template bool almost_equal(double x, double y, int ulp);
template bool almost_equal(long double x, long double y, int ulp);

#include <cmath>
#include <limits>
#include <type_traits>
#include <algorithm>

#include "almost_equal.h"

using namespace std;

template<typename T> bool almost_equal(T x, T y, unsigned int ulp)
{
   // the IEEE standard says that any comparison operation involving a NAN must return false
   if( isnan(x) || isnan(y) )
      return false;
   
   // before comparison, the machine epsilon has to be scaled to the magnitude of the values and multiplied by the required precision in units in the last place (ULP)
   return abs(x-y) <= abs(numeric_limits<T>::epsilon()*x+numeric_limits<T>::epsilon()*y) * ulp;
}
// explicitly create template definitions
template bool almost_equal(float x, float y, unsigned int ulp);
template bool almost_equal(double x, double y, unsigned int ulp);
template bool almost_equal(long double x, long double y, unsigned int ulp);

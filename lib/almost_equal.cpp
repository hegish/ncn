#include "almost_equal.h"
#include <cmath>
#include <limits>
#include <type_traits>
#include <algorithm>

using namespace std;


template<typename T> bool almost_equal_vectors(std::vector<T> x, std::vector<T> y, unsigned int ulp)
{
   if(x.size() != y.size())
      return false;
   
   for(int i = 0; i < x.size(); i++)
   {
      if(!almost_equal(x[i], y[i], ulp))
         return false;
   }
   
   return true;
}


template<typename T> bool almost_equal(T x, T y, unsigned int ulp)
{
   // the IEEE standard says that any comparison operation involving a NAN must return false
   if( std::isnan(x) || std::isnan(y) ) // there is an issue with the old intel icpc 17.0.2 if we use just plain isnan instead of std::isnan
      return false;
   
   // before comparison, the machine epsilon has to be scaled to the magnitude of the values and multiplied by the required precision in units in the last place (ULP)
   return abs(x-y) <= abs(numeric_limits<T>::epsilon()*x+numeric_limits<T>::epsilon()*y) * ulp;
}


// explicitly create template definitions

template bool almost_equal_vectors(std::vector<float> x, std::vector<float> y, unsigned int ulp);
template bool almost_equal_vectors(std::vector<double> x, std::vector<double> y, unsigned int ulp);
template bool almost_equal_vectors(std::vector<long double> x, std::vector<long double> y, unsigned int ulp);

template bool almost_equal(float x, float y, unsigned int ulp);
template bool almost_equal(double x, double y, unsigned int ulp);
template bool almost_equal(long double x, long double y, unsigned int ulp);

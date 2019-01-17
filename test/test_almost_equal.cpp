#include "gtest/gtest.h"
#include "almost_equal.h"
#include <stdlib.h>

#include <cmath>

using namespace std;

namespace {

   TEST(ncn, almostequalxx)
   {
      double d1 = 0.2;
      double d2 = 1 / sqrt(5) / sqrt(5);

      EXPECT_DOUBLE_EQ(d1, d2);
      EXPECT_TRUE(almost_equal(d1, d2, 2));

      cout<<"F min "<<numeric_limits<float>::min()<<" F max "<<numeric_limits<float>::max()<<endl;
      cout<<"min "<<numeric_limits<double>::min()<<" max "<<numeric_limits<double>::max()<<endl;
      cout<<"L min "<<numeric_limits<long double>::min()<<" L max "<<numeric_limits<long double>::max()<<endl;
   }

}  // namespace

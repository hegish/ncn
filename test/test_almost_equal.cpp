#include "gtest/gtest.h"
#include "almost_equal.h"
#include <stdlib.h>

#include <cmath>

using namespace std;

namespace {

   TEST(ncn_almostequal, simpledoubles)
   {
      double d1 = 0.2;
      double d2 = 1 / sqrt(5) / sqrt(5);

      EXPECT_DOUBLE_EQ(d1, d2);
      EXPECT_TRUE(almost_equal(d1, d2, 2));

      cout<<"F min "<<numeric_limits<float>::min()<<" F max "<<numeric_limits<float>::max()<<endl;
      cout<<"min "<<numeric_limits<double>::min()<<" max "<<numeric_limits<double>::max()<<endl;
      cout<<"L min "<<numeric_limits<long double>::min()<<" L max "<<numeric_limits<long double>::max()<<endl;
   }

   
   TEST(ncn_almostequal, big_numeric_limits)
   {
      EXPECT_TRUE(almost_equal(numeric_limits<float>::max(), numeric_limits<float>::max(), 2));
      EXPECT_FALSE(almost_equal(numeric_limits<float>::max()*0.51, numeric_limits<float>::max()*0.54, 2));
   }
   
   
   TEST(ncn_almostequal, bignums)
   {
      EXPECT_TRUE(almost_equal(2.0e38F, 2.0e38F, 2));
      EXPECT_FALSE(almost_equal(2.1e38F, 2.4e38F, 2));
      EXPECT_TRUE(almost_equal(2.000000001e38F, 2.000000004e38F, 2));
      EXPECT_FALSE(almost_equal(2.000001e37F, 2.000004e37F, 2));
   }


   TEST(ncn_almostequal, bigandsmallnums)
   {
      EXPECT_FALSE(almost_equal(2.0e30F, 2.0e-30F, 2));
   }
   
}  // namespace

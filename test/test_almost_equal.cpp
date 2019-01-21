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
   }

   
   TEST(ncn_almostequal, small_numeric_limits)
   {
      EXPECT_TRUE(almost_equal(numeric_limits<float>::min(), numeric_limits<float>::min(), 2));
      EXPECT_FALSE(almost_equal(numeric_limits<float>::min()*1.11, numeric_limits<float>::min()*1.14, 2));

      EXPECT_TRUE(almost_equal(numeric_limits<double>::min(), numeric_limits<double>::min(), 2));
      EXPECT_FALSE(almost_equal(numeric_limits<double>::min()*1.11, numeric_limits<double>::min()*1.14, 2));

      EXPECT_TRUE(almost_equal(numeric_limits<long double>::min(), numeric_limits<long double>::min(), 2));
      EXPECT_FALSE(almost_equal(numeric_limits<long double>::min()*1.11, numeric_limits<long double>::min()*1.14, 2));
   }

   
   TEST(ncn_almostequal, big_numeric_limits)
   {
      EXPECT_TRUE(almost_equal(numeric_limits<float>::max(), numeric_limits<float>::max(), 2));
      EXPECT_FALSE(almost_equal(numeric_limits<float>::max()*0.51, numeric_limits<float>::max()*0.54, 2));
   }
   
   
   TEST(ncn_almostequal, smallnums)
   {
      EXPECT_TRUE(almost_equal(0.2, 0.2, 2));
      EXPECT_TRUE(almost_equal(0.2000000F, 0.20000001F, 2));
      EXPECT_FALSE(almost_equal(0.200000L, 0.2000001L, 2));

      EXPECT_TRUE(almost_equal(2.0e-38F, 2.0e-38F, 2));
      EXPECT_FALSE(almost_equal(2.1e-37F, 2.4e-37F, 2));

      EXPECT_FALSE(almost_equal(2.1e-4930L, 2.4e-4930L, 2));
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

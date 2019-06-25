#include "gtest/gtest.h"
#include <stdlib.h>

#include "globals.h"
#include "time_increases.h"

using namespace std;


namespace {

   
   TEST(ncn_assert_time_increases, 1_2_3_increases)
   {
      vector<double> data = {1.0, 2.0, 3.0};
      EXPECT_EQ(0, ncn::increases(data));
   }


   TEST(ncn_assert_time_increases, 1_0_3_increases_not)
   {
      vector<double> data = {1.0, 0.0, 3.0};
      EXPECT_EQ(1, ncn::increases(data));
   }


   TEST(ncn_assert_time_increases, single_value_increases)
   {
      vector<double> data = {1.0};
      EXPECT_EQ(0, ncn::increases(data));
   }

}  // namespace

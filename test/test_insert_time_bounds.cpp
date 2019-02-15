#include "gtest/gtest.h"
#include <stdlib.h>

#include "globals.h"
#include "insert_time_bounds.h"

using namespace std;
using namespace ncn;

namespace {

   TEST(ncn_insert_time_bounds, can_compute_time_bounds)
   {
      vector<double> times = {15.5, 45, 74.5, 105, 135.5, 166, 196.5, 227.5, 258, 288.5, 319, 349.5};
      // 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365
      vector< vector<double> > bounds;
      EXPECT_NO_THROW( ncn::compute_time_bounds(times, bounds) );

      vector< vector<double> > exp_bounds = {{0.0, 31.0}, {31.0, 59.0}, {59.0, 90.0}, {90.0, 120.0}, {120.0, 151.0}, {151.0, 181.0}, {181.0, 212.0}, {212.0, 243.0}, {243.0, 273.0}, {273.0, 304.0}, {304.0, 334.0}, {334.0, 365.0}};
      EXPECT_EQ(exp_bounds.size(), bounds.size());
      for(int i = 0; i < times.size(); i++)
      {
         EXPECT_DOUBLE_EQ(exp_bounds[i][0], bounds[i][0]);
         EXPECT_DOUBLE_EQ(exp_bounds[i][1], bounds[i][1]);
      }
   }

}  // namespace

#include "gtest/gtest.h"
#include <stdlib.h>
#include <netcdf>
#include <chrono>

#include "globals.h"
#include "tail_zeros.h"

using namespace std;
using namespace netCDF;
using namespace ncn;


namespace {

   
   TEST(ncn_tail_zeros, can_find_0_zeros)
   {
      string inpath = fixture_dir+"/tail_zeros.nc";
      
      EXPECT_EQ(0, number_of_tail_zeros(inpath, "yadda"));
   }


   TEST(ncn_tail_zeros, can_find_zeros_in_two_levels)
   {
      string inpath = fixture_dir+"/tail_zeros.nc";
      
      EXPECT_EQ(6, number_of_tail_zeros(inpath, "temp"));
   }

   
   TEST(ncn_tail_zeros, can_find_zeros_in_1d)
   {
      string inpath = fixture_dir+"/tail_zeros.nc";
      
      EXPECT_EQ(1, number_of_tail_zeros(inpath, "time"));
   }

   
   TEST(ncn_tail_zeros, throws_if_variable_does_not_exist)
   {
      string inpath = fixture_dir+"/tail_zeros.nc";
      
      EXPECT_ANY_THROW(number_of_tail_zeros(inpath, "nosuchvariable"));
   }

}  // namespace

#include "gtest/gtest.h"
#include <stdlib.h>

#include "globals.h"
#include "compare_netcdf.h"

using namespace std;
using namespace ncn;

namespace {

   TEST(ncn_compare, canopennetcdffile)
   {
      vector<float> data;
      EXPECT_ANY_THROW( ncn::read_data(fixture_dir+"/nosuchfile_406B39B9_5FDC_4B8C_B777_EB81ADE825CD.nc", "varname", {0}, {1}, data));
      
      EXPECT_NO_THROW( ncn::read_data(fixture_dir+"/tos.nc", "tos", {0,0}, {1,1}, data) );
   }


   TEST(ncn_compare, canreadnetcdfdata)
   {
      vector<float> data;
      ncn::read_data(fixture_dir+"/tos.nc", "tos", {0,0},
                                                   {2,1}, data); // two time indices, one value each
      
      EXPECT_FLOAT_EQ(-1.84166586F, data[0]);
      EXPECT_FLOAT_EQ(-2.84166586F, data[1]);
   }
   
}  // namespace

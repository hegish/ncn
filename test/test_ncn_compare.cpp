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
   
   
   TEST(ncn_compare, throws_if_expecting_double_but_got_float)
   {
      vector<double> data;
      EXPECT_THROW(ncn::read_data(fixture_dir+"/tos.nc", "tos", {0,0}, {2,1}, data),
                   std::runtime_error);
   }
   
   
   TEST(ncn_compare, can_call_almost_equal_netcdf_data_explicit)
   {
      string filepath_a = fixture_dir+"/tos.nc";
      std::string varname_a = "tos";
      vector<size_t> indices_a = {0,0};
      vector<size_t> sizes_a = {1,1};
      
      string filepath_b = fixture_dir+"/tos.nc";
      string varname_b = "tos";
      vector<size_t> indices_b = {0,0};
      vector<size_t> sizes_b = {1,1};
      bool eq = almost_equal_netcdf_data_explicit<float>(filepath_a, varname_a, indices_a, sizes_a, filepath_b, varname_b, indices_b, sizes_b);
      EXPECT_TRUE(eq);
   }


   TEST(ncn_compare, can_call_almost_equal_netcdf_data)
   {
      string filepath_a = fixture_dir+"/tos.nc";
      std::string varname_a = "tos";
      vector<size_t> indices_a = {0,0};
      vector<size_t> sizes_a = {1,1};
      
      string filepath_b = fixture_dir+"/tos.nc";
      string varname_b = "tos";
      vector<size_t> indices_b = {0,0};
      vector<size_t> sizes_b = {1,1};
      bool eq = almost_equal_netcdf_data(filepath_a, varname_a, indices_a, sizes_a, filepath_b, varname_b, indices_b, sizes_b);
      EXPECT_TRUE(eq);
   }

}  // namespace

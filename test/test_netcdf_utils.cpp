#include "gtest/gtest.h"
#include <stdlib.h>

#include "globals.h"
#include "netcdf_utils.h"

using namespace std;
using namespace ncn;

namespace {

   TEST(ncn_netcdf_utils, canreadtype)
   {
      const type_info& actual_type = read_data_type(fixture_dir+"/tos.nc", "tos");
      EXPECT_EQ(typeid(float), actual_type);
   }
}  // namespace

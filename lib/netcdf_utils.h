#ifndef netcdf_utils_2ED0C2D0_721A_42D3_ACFC_B96486BBEFCC
#define netcdf_utils_2ED0C2D0_721A_42D3_ACFC_B96486BBEFCC

#include <string>
#include <vector>

namespace netCDF
{
   class NcType;
}

namespace ncn
{
   const std::type_info& read_data_type(const std::string filepath, const std::string varname);
   const std::type_info& plain_type_for_nctype(const netCDF::NcType nctype);
}

#endif

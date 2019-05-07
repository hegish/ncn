#ifndef transpose_5BAB4E7A_6851_4951_A161_53C4B2EF392C
#define transpose_5BAB4E7A_6851_4951_A161_53C4B2EF392C

#include <string>

namespace ncn
{
   void transpose_netcdf_dimensions(const std::string inpath, const std::string outpath, const std::string varname, const std::vector<std::string>& transpose_dimnames);
}
#endif

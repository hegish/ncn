#ifndef compare_netcdf_6CB42D38_C5E5_4776_A717_9A5784153260
#define compare_netcdf_6CB42D38_C5E5_4776_A717_9A5784153260

#include <string>
#include <vector>

namespace ncn
{
   template<typename T> void read_data(const std::string filepath, const std::string varname, const std::vector<size_t>& indices, const std::vector<size_t>& sizes, std::vector<T>& data);
}

#endif

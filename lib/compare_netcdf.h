#ifndef compare_netcdf_6CB42D38_C5E5_4776_A717_9A5784153260
#define compare_netcdf_6CB42D38_C5E5_4776_A717_9A5784153260

#include <string>
#include <vector>

namespace ncn
{
   bool almost_equal_netcdf_data(const std::string filepath_a, const std::string varname_a, const std::vector<size_t>& indices_a, const std::vector<size_t>& sizes_a, const std::string filepath_b, const std::string varname_b, const std::vector<size_t>& indices_b, const std::vector<size_t>& sizes_b);
   template<typename T> void read_data(const std::string filepath, const std::string varname, const std::vector<size_t>& indices, const std::vector<size_t>& sizes, std::vector<T>& data);
}

#endif

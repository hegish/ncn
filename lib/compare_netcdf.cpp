#include "compare_netcdf.h"
#include <netcdf>
#include <sstream>
#include <numeric>
#include "almost_equal.h"

using namespace std;
using namespace netCDF;

namespace ncn
{
   bool almost_equal_netcdf_data(const std::string filepath_a, const std::string varname_a, const std::vector<size_t>& indices_a, const std::vector<size_t>& sizes_a, const std::string filepath_b, const std::string varname_b, const std::vector<size_t>& indices_b, const std::vector<size_t>& sizes_b)
   {
      // TODO: this is hard coded for float comparison. how to neatly select the right data type?

      vector<float> data_a;
      ncn::read_data(filepath_a, varname_a, indices_a, sizes_a, data_a);

      vector<float> data_b;
      ncn::read_data(filepath_b, varname_b, indices_b, sizes_b, data_b);
      
      return almost_equal_vectors(data_a, data_b, 2);
   }
   
   
   template<typename T> void read_data(const std::string filepath, const std::string varname, const std::vector<size_t>& indices, const std::vector<size_t>& sizes, std::vector<T>& data)
   {
      if(indices.size() != sizes.size())
      {
         std::stringstream msg;
         msg<<__FILE__<<":"<<__LINE__<<" indices and sizes do not have the same number of items <"<<indices.size()<<"> vs <"<<sizes.size()<<">";
         throw std::runtime_error(msg.str());
      }
      
      NcFile *ncf; // use pointer so we can wrap the instantiation in a try catch block
      try
      {
         ncf = new NcFile(filepath, NcFile::read);
      }
      catch(const std::exception& e)
      {
         std::stringstream msg;
         msg<<__FILE__<<":"<<__LINE__<<" can not open file <"<<filepath<<">";
         throw std::runtime_error(msg.str());
      }

      NcVar var = ncf->getVar(varname);
      if(var.isNull())
      {
         std::stringstream msg;
         msg<<__FILE__<<":"<<__LINE__<<" <"<<filepath<<"> has no variable named <"<<varname<<">";
         throw std::runtime_error(msg.str());
      }


      if(var.getDimCount() != indices.size())
      {
         std::stringstream msg;
         msg<<__FILE__<<":"<<__LINE__<<" "<<filepath<<" "<<varname<<" has <"<<var.getDimCount()<<"> dimensions but we got indices for <"<<sizes.size()<<"> dimensions";
         throw std::runtime_error(msg.str());
      }
      
      // TODO: should we check the data type of the netcdf variable against our data vector?

      // read everything in one go, as we assume we do not read too big amounts of data here
      // e.g. for 10 years 3 hourly data we would have 29216 timesteps, which would require about 234 kB of storage if we would read 1 double value for each timestep
      data.resize(accumulate(sizes.begin(), sizes.end(), 1, multiplies<size_t>()));
      var.getVar(indices, sizes, &data[0]);

      delete ncf;
   }

   // explicitly instantiate the templates for every type we need
   template void read_data(const std::string filepath, const std::string varname, const std::vector<size_t>& indices, const std::vector<size_t>& sizes, std::vector<float>& data);
   template void read_data(const std::string filepath, const std::string varname, const std::vector<size_t>& indices, const std::vector<size_t>& sizes, std::vector<double>& data);
}

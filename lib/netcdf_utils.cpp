#include "netcdf_utils.h"
#include <netcdf>
#include <sstream>

using namespace std;
using namespace netCDF;

namespace ncn
{
   const std::type_info& plain_type_for_nctype(const netCDF::NcType nctype)
   {
      if(nctype == netCDF::ncFloat)
         return typeid(float);
      else if(nctype == netCDF::ncDouble)
         return typeid(double);
      else
      {
         std::stringstream msg;
         msg<<__FILE__<<":"<<__LINE__<<" unknown NcType <"<<nctype.getName()<<">";
         throw std::runtime_error(msg.str());
      }
   }
   
   
   const std::type_info& read_data_type(const std::string filepath, const std::string varname)
   {
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
      
      // return a plain old data type so we do not expose the netcdf types
      NcType actual_type = var.getType();
      const type_info& plain_type = plain_type_for_nctype(actual_type);
      
      delete ncf;
      
      return plain_type;
   }
}

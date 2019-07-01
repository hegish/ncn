#include "time_increases.h"
#include <netcdf>


using namespace std;
using namespace netCDF;

namespace ncn
{
   // returns the first index whose data value is not bigger than the value before
   size_t increases(std::vector<double> &data)
   {
      for(size_t i = 0; i+1 < data.size(); i++)
      {
         if((i+1) < (data.size()))
         {
            if(data[i] >= data[i+1])
               return i+1;
         }
      }
      
      return 0; // all values increase
   }

   
   bool check_time_increases(const std::string filepath)
   {
      NcFile ncf(filepath, NcFile::read);
      NcVar time_var = ncf.getVar("time");
      if(time_var.getDimCount() != 1) throw std::runtime_error("variable time has dimension != 1 <"+filepath+">");

      NcDim tdim = time_var.getDim(0);
      if(tdim.getName() != "time") throw std::runtime_error("expected first dimension of time to be named 'time' <"+filepath+">");

      vector<double> times(tdim.getSize());
      time_var.getVar(&times[0]);
      if(times.empty()) throw std::runtime_error("time has no values <"+filepath+">");

      size_t error_index = increases(times);
      if(0 != error_index)
         cout<<fixed<<"decrease: ["<<error_index-1<<"] "<<times[error_index-1]<<", ["<<error_index<<"] "<<times[error_index]<<" "<<filepath<<"\n";
      
      return 0 == error_index;
   }

}

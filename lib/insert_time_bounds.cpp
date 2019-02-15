#include "insert_time_bounds.h"

#include <netcdf>
#include <sstream>
#include <numeric>

using namespace std;
using namespace netCDF;

namespace ncn
{
   void insert_time_bounds(const std::string filepath)
   {
      NcFile ncf(filepath, NcFile::write);
      NcVar time_var = ncf.getVar("time");
      if(time_var.getDimCount() != 1) throw std::runtime_error("variable time has dimension != 1 <"+filepath+">");
     
      NcDim tdim = time_var.getDim(0);
      if(tdim.getName() != "time") throw std::runtime_error("expected first dimension of time to be named 'time' <"+filepath+">");
     
      vector<double> times(tdim.getSize());
      time_var.getVar(&times[0]);
      if(times.empty()) throw std::runtime_error("time has no values <"+filepath+">");

      vector<double> bounds;
      compute_time_bounds(times, bounds);

      NcDim number_of_time_bounds_dim = ncf.addDim("number_of_time_bounds", 2);
      NcVar time_bounds_var = ncf.addVar("time_bnds", ncDouble, {tdim, number_of_time_bounds_dim});
      time_bounds_var.putVar(&bounds[0]);
      
      // we also have to add an attribute to the time variable
      time_var.putAtt("bounds", time_bounds_var.getName());
   }
    
    
   void compute_time_bounds(const std::vector<double> &times, std::vector<double> &flat_bounds)
   {
      const int number_of_time_bounds = 2;
      flat_bounds.resize(times.size()*number_of_time_bounds);
      if(times.size() == 0)
      return;

      flat_bounds[0] = 0.0;
      flat_bounds[1] = 2*times[0];
      for(int i = 1; i < times.size(); i++)
      {
         double previous_end_bound = flat_bounds[(i-1)*2+1];
         flat_bounds[i*2] = previous_end_bound;
         flat_bounds[i*2+1] = 2*times[i] -previous_end_bound;
      }
   }
}

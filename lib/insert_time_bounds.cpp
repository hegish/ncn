#include "insert_time_bounds.h"

#include <netcdf>
#include <sstream>
#include <numeric>

using namespace std;
using namespace netCDF;

namespace ncn
{
   void compute_time_bounds(const std::vector<double> &times, std::vector< std::vector<double> > &bounds)
   {
      bounds.resize(times.size());
      if(times.size() == 0)
         return;

      bounds[0] = {0.0, 2*times[0]};
      for(int i = 1; i < bounds.size(); i++)
      {
         double previous_end_bound = bounds[i-1][1];
         bounds[i] = {previous_end_bound, 2*times[i] -previous_end_bound};
      }
   }

}

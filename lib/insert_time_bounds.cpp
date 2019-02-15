#include "insert_time_bounds.h"

#include <netcdf>
#include <sstream>
#include <numeric>

using namespace std;
using namespace netCDF;

namespace ncn
{

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

#include "mean_timestamp_adjust.h"

#include <iomanip>
#include <cstdlib>
#include <netcdf>

using namespace std;
using namespace netCDF;

namespace ncn
{
  /*
    move timestamp from the end of a mean interval to the middle of each interval as required here:
    http://cmip-pcmdi.llnl.gov/cmip5/docs/CMIP5_output_metadata_requirements.pdf <http://cmip-pcmdi.llnl.gov/cmip5/docs/CMIP5_output_metadata_requirements.pdf
    page 9 "For time-mean data, a time coordinate value must be defined as the mid-point of the interval over which the average is computed."
    */
   void adjust_timestamps_end_to_middle(std::vector<double> &times)
   {

      vector<double> orig(times.size());
      times.swap(orig);
      
      times[0] = 0.5*orig[0];
      for(int i = 1; i < times.size(); i++)
         times[i] = orig[i-1]+0.5*(orig[i]-orig[i-1]);
   }


   // move timestamps of passed files forward to the middle of the time interval, files are changed in place
   void mean_timestamp_adjust(const std::string filepath)
   {
      NcFile ncf(filepath, NcFile::write);
      NcVar time_var = ncf.getVar("time");
      if(time_var.getDimCount() != 1) throw std::runtime_error("variable time has dimension != 1 <"+filepath+">");

      NcDim tdim = time_var.getDim(0);
      if(tdim.getName() != "time") throw std::runtime_error("expected first dimension of time to be named 'time' <"+filepath+">");

      vector<double> times(tdim.getSize());
      time_var.getVar(&times[0]);
      if(times.empty()) throw std::runtime_error("time has no values <"+filepath+">");

      double a = times.front();
      double z = times.back();
      adjust_timestamps_end_to_middle(times);
      time_var.putVar(&times[0]);
      cout<<fixed<<filepath<<" t1: "<<a<<" => "<<times.front()<<" .. t"<<times.size()<<": "<<z<<" => "<<times.back()<<"\n";
   }
}

#ifndef mean_timestamp_adjust_00B2647A_5C56_45BC_8815_9545FE4B900B
#define mean_timestamp_adjust_00B2647A_5C56_45BC_8815_9545FE4B900B

#include <string>
#include <vector>

namespace ncn
{
   void adjust_timestamps_end_to_middle(std::vector<double> &times);
   void mean_timestamp_adjust(const std::string filepath);
}

#endif

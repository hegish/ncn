#include "time_increases.h"


using namespace std;

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

}

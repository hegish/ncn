#include "time_increases.h"


using namespace std;

namespace ncn
{
   bool increases(std::vector<double> &data)
   {
      for(size_t i = 0; i < data.size()-1; i++)
      {
         if((i+1) < (data.size()))
         {
            if(data[i] >= data[i+1])
               return false;
         }
      }
      
      return true;
   }

}

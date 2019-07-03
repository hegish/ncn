#include "tail_zeros.h"
#include <netcdf>
#include "almost_equal.h"
#include <numeric>
#include <sstream>


using namespace std;
using namespace netCDF;

namespace ncn
{
   void decrement(vector<size_t>& indices, size_t outermost_index_to_decrement, const vector<size_t>& dim_sizes)
   {
      if(indices[outermost_index_to_decrement] > 0)
         indices[outermost_index_to_decrement] --;
      else
      {
         // we are at 0, reset this index to max and decrement the index of the next dimension
         indices[outermost_index_to_decrement] = dim_sizes[outermost_index_to_decrement]-1;
         {
            if(indices[outermost_index_to_decrement-1] == 0 && outermost_index_to_decrement-1 == 0)
               return;
            
            decrement(indices, outermost_index_to_decrement-1, dim_sizes);
         }
      }
   }
   
   
   size_t number_of_tail_zeros(const NcVar& var)
   {
      vector<NcDim> dims = var.getDims();
      
      size_t zeros_count = 0;
      float value;
      vector<size_t> dim_sizes(dims.size());
      for(int i = 0; i < dim_sizes.size(); i++)
         dim_sizes[i] = dims[i].getSize();
      
      size_t total_size = accumulate(dim_sizes.begin(), dim_sizes.end(), 1, multiplies<size_t>());

      vector<size_t> indices(dims.size());
      for(int i = 0; i < indices.size(); i++)
         indices[i] = dim_sizes[i]-1;

      int current_dim_index = dim_sizes.size()-1;
      for(int i = 0; i < total_size; i++)
      {
         var.getVar(indices, &value);
         if(almost_equal(0.0F, value, 2))
            zeros_count ++;
         else
            break;

         decrement(indices, current_dim_index, dim_sizes);
      }
     
      return zeros_count;
   }

   
   size_t number_of_tail_zeros(const std::string filepath, const std::string varname)
   {
      NcFile ncf(filepath, NcFile::read);
      
      NcVar var = ncf.getVar(varname);
      
      if(var.isNull())
      {
         std::stringstream msg;
         msg<<__FILE__<<":"<<__LINE__<<" can not find variable <"<<varname<<"> in file <"<<filepath<<">";
         throw std::runtime_error(msg.str());
      }
      
      return number_of_tail_zeros(var);      
   }


   void report_tail_zeros(const std::string filepath)
   {
      NcFile ncf(filepath, NcFile::read);
      
      multimap<string, NcVar> vars = ncf.getVars();
      for(multimap<string, NcVar>::iterator it = vars.begin(); it != vars.end(); ++it)
      {
         NcVar var = it->second;
         size_t zeros_count = number_of_tail_zeros(var);
         if(zeros_count > 0)
            cout<<zeros_count<<" zero values at end of '"<<var.getName()<<"' "<<filepath<<endl;
      }
   }

}

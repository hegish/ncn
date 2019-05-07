#include "transpose.h"
#include <netcdf>
#include <sstream>

using namespace std;
using namespace netCDF;


namespace ncn
{
   void transpose_netcdf_dimensions(const std::string inpath, const std::string outpath, const std::string varname, const std::vector<std::string>& transpose_dimnames)
   {      
      NcFile *ncf; // use pointer so we can wrap the instantiation in a try catch block
      try
      {
         ncf = new NcFile(inpath, NcFile::read);
      }
      catch(const std::exception& e)
      {
         std::stringstream msg;
         msg<<__FILE__<<":"<<__LINE__<<" can not open file <"<<inpath<<">";
         throw std::runtime_error(msg.str());
      }
      
      NcVar var = ncf->getVar(varname);
      if(var.isNull())
      {
         std::stringstream msg;
         msg<<__FILE__<<":"<<__LINE__<<" <"<<inpath<<"> has no variable named <"<<varname<<">";
         throw std::runtime_error(msg.str());
      }
      
      // get hold of the dims we should transpose
      vector<NcDim> dims = var.getDims();
      NcDim dim_a;
      NcDim dim_b;
      for(int i = 0; i < dims.size(); i++)
      {
         NcDim d = dims[i];
         if(d.getName() == transpose_dimnames[0])
         {
            dim_a = d;
            d = dims[i+1];
            if(d.getName() != transpose_dimnames[1])
            {
               std::stringstream msg;
               msg<<__FILE__<<":"<<__LINE__<<" second dim <"<<transpose_dimnames[1]<<"> does not follow first dim <"<<transpose_dimnames[0]<<"> <"<<inpath<<">";
               throw std::runtime_error(msg.str());
            }
            dim_b = d;
            break;
         }
      }
      
      NcFile outfile(outpath, NcFile::replace);
      
      for(NcDim d : dims)
         outfile.addDim(d.getName(), d.getSize());
      
      vector<NcDim> transposed_dims = {dims[0], dim_b, dim_a};
      NcVar transposed_var = outfile.addVar(var.getName(), var.getType(), transposed_dims);

      for(size_t i = 0; i < dim_b.getSize(); i++)
      {
         vector<float> data(dim_a.getSize());
         vector<size_t> indices = {0,0,0+i};
         vector<size_t> sizes = {1, dim_a.getSize(), 1};
         var.getVar(indices, sizes, &data[0]);
         
         vector<size_t> indicesT = {0,0+i,0};
         vector<size_t> sizesT = {1, 1, dim_a.getSize()};
         transposed_var.putVar(indicesT, sizesT, &data[0]);
      }

      delete ncf;
   }
}

#include "transpose.h"
#include <netcdf>
#include <sstream>

using namespace std;
using namespace netCDF;


namespace ncn
{
   void transpose_netcdf_dimensions(const std::string inpath, const std::string outpath, const std::string varname, const std::vector<std::string>& transposed_dimnames)
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
      
      // get hold of the dims given as dimnames
      vector<NcDim> dims = var.getDims();
      if(dims.size() != transposed_dimnames.size())
      {
         std::stringstream msg;
         msg<<__FILE__<<":"<<__LINE__<<" number of dimensions do not match, input has <"<<dims.size()<<">, output should have <"<<transposed_dimnames.size()<<"> for variable <"<<varname<<"> of file <"<<inpath<<">";
         throw std::runtime_error(msg.str());
      }

      vector<NcDim> transposed_dims;
      vector<size_t> transposed_dims_indices;
      for(const string n : transposed_dimnames)
      {
         // find dim with this name
         for(size_t i = 0; i < dims.size(); i++)
         {
            NcDim d = dims[i];
            if(d.getName() == n)
            {
               transposed_dims.push_back(d);
               transposed_dims_indices.push_back(i);
               break;
            }
            else if(i == dims.size()-1)
            {
               std::stringstream msg;
               msg<<__FILE__<<":"<<__LINE__<<" can not find dimension <"<<n<<"> for variable <"<<varname<<"> of file <"<<inpath<<">";
               throw std::runtime_error(msg.str());
            }
         }
      }
      
      NcFile outfile(outpath, NcFile::newFile);
      // copy over the dims
      for(const NcDim d : dims)
         outfile.addDim(d.getName(), d.getSize());
      
      NcVar transposed_var = outfile.addVar(var.getName(), var.getType(), transposed_dims);

      if( (vector<size_t>){0,2,1} == transposed_dims_indices )
      {
         // this is not generic, but only for the case of three dimensions of which the last two are being swapped (i.e. 0,2,1)
         for(size_t t = 0; t < dims[0].getSize(); t++)
         {
            for(size_t i = 0; i < transposed_dims[1].getSize(); i++)
            {
               vector<float> data(transposed_dims[2].getSize());
               vector<size_t> indices = {t,0,i};
               vector<size_t> sizes = {1, transposed_dims[2].getSize(), 1};
               var.getVar(indices, sizes, &data[0]);

               vector<size_t> indicesT = {t,i,0};
               vector<size_t> sizesT = {1, 1, transposed_dims[2].getSize()};
               transposed_var.putVar(indicesT, sizesT, &data[0]);
            }
         }
      }
      else
      {
         std::stringstream msg;
         msg<<__FILE__<<":"<<__LINE__<<" can not transpose to <";
         for(size_t i = 0; i < transposed_dims_indices.size()-1; i++)
            msg<<transposed_dims_indices[i]<<", ";
         if(transposed_dims_indices.size() > 0)
            msg<<transposed_dims_indices.back();
         msg<<"> for variable <"<<varname<<"> of file <"<<inpath<<">";
         throw std::runtime_error(msg.str());
      }

      delete ncf;
   }
}

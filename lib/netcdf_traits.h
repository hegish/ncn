#ifndef nctype_trait_6CC26A41_301B_469E_96BD_2CA0800C2CA0
#define nctype_trait_6CC26A41_301B_469E_96BD_2CA0800C2CA0

namespace ncn
{   
   template<typename T> netCDF::NcType nctype_trait();

   
   template<> netCDF::NcType nctype_trait<float>()
   {
      return netCDF::ncFloat;
   }
   
   
   template<> netCDF::NcType nctype_trait<double>()
   {
      return netCDF::ncDouble;
   }   
}

#endif

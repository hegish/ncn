#include <iostream>
#include "compare_netcdf.h"

using namespace std;

int compare_tos_thetao_command(const std::vector<std::string> args)
{
   string filepath_a = args[0];
   std::string varname_a = "tos";
   vector<size_t> indices_a = {0,0};
   vector<size_t> sizes_a = {1,1};
   
   string filepath_b = args[1];
   string varname_b = "thetao";
   vector<size_t> indices_b = {0,0,0};
   vector<size_t> sizes_b = {1,1,1};
   bool eq = ncn::almost_equal_netcdf_data<float>(filepath_a, varname_a, indices_a, sizes_a, filepath_b, varname_b, indices_b, sizes_b);
   
   cout<<"equal? "<<(eq?"yes":"no")<<endl;
   return eq? 0:1;
}


int main(int argc, const char * argv[])
{
   vector<string> args(argv+1, argv+argc); // without argv[0]

   if(args.size() > 0)
   {
      vector<string> subargs(args.begin()+1, args.end());

      if("compare_tos_thetao" == args[0])
      {
         return compare_tos_thetao_command(subargs);
      }
      
   }

   return 0;
}

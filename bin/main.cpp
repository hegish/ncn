#include <iostream>
#include "compare_netcdf.h"
#include <sstream>
#include "subcommand_line_interface.h"
#include "insert_time_bounds.h"

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
   bool eq = ncn::almost_equal_netcdf_data(filepath_a, varname_a, indices_a, sizes_a, filepath_b, varname_b, indices_b, sizes_b);
   
   cout<<"equal? "<<(eq?"yes":"no")<<endl;
   return eq? 0:1;
}


int insert_time_bounds_command(const std::vector<std::string> args)
{
   string filepath = args[0];
   ncn::insert_time_bounds(filepath);
   
   return 0;
}


int main(int argc, const char * argv[])
{
   Subcommand &cli = Subcommand::instance();
   
   cli.add("compare_tos_thetao", compare_tos_thetao_command);
   cli.add("insert_time_bounds", insert_time_bounds_command); // assume adjusted mean timestamps, i.e. time is in the middle of each mean interval

   return cli.execute(argc, argv);
}

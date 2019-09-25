#include "gtest/gtest.h"
#include "globals.h"

std::string fixture_dir; // declare global variable at file scope

int main(int argc, char **argv)
{
   if(argc < 2)
      throw std::runtime_error("missing path to fixtures dir in args");

   ::testing::InitGoogleTest(&argc, argv);
   
   // set fixture dir from argv
   std::vector<std::string> args(argv+1, argv+argc);
   fixture_dir = args[0];
   
   return RUN_ALL_TESTS();
}

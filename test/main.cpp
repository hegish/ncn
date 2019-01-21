#include "gtest/gtest.h"
#include "globals.h"

std::string fixture_dir; // declare global variable at file scope

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   
   // set fixture dir from argv
   std::vector<std::string> args(argv+1, argv+argc);
   assert(args.size() > 0);
   fixture_dir = args[0];
   
   return RUN_ALL_TESTS();
}

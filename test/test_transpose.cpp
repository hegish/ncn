#include "gtest/gtest.h"
#include <stdlib.h>
#include <netcdf>
#include <chrono>

#include "globals.h"
#include "transpose.h"

using namespace std;
using namespace netCDF;
using namespace ncn;


namespace {

   
   TEST(ncn_rowcol, can_read)
   {
      string inpath = fixture_dir+"/transpose.nc";
      string outpath = "./transpose.nc.2A1F0DB9_BA11_4321_8666_1A232DEC6B30";

      ncn::transpose_netcdf_dimensions(inpath, outpath, "temp", {"nod2", "nz1"}); // time, nod2, nz1 => time, nz1, nod2


      string cmd = "/usr/local/bin/ncdump "+outpath;
      system(cmd.c_str());

      cmd = "rm "+outpath;
      system(cmd.c_str());
   }

}  // namespace

# ncn README file

ncn is a command line software written in C++ to manipulate NetCDF files via certain commands. ncn is tailored to do NetCDF file changes in place, i.e. without creating new or temporary files. Its main intent is to alter output files from the Sea-ice Ocean Model (FESOM) of the Alfred Wegener Institute (AWI). ncn is also utilized by the seamore cmorization software. [https://github.com/FESOM/seamore](https://github.com/FESOM/seamore)

Any feedback is greatly appreciated, please mail to: Jan Hegewald <jan.hegewald@awi.de>

# Basic Usage

From the command line type
`ncn` to show a list of commands. These are currently:

```
=== known sub-commands:
check_time_increases
compare_tos_thetao
help
insert_time_bounds
mean_timestamp_adjust
report_tail_zeros
transpose
===
```

# Build notes

1. If the current platform is included in `env/<plaform_dir>` and contains a `shell`
   script, then you can use:
   ```
   source env.sh
   ```
   Otherwise, try to setup the correct environment for the current platform taking as an
   example `env/albedo/shell`

2. Execute:
   ```
   cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Release /path/ncn_src/
   make
   ```

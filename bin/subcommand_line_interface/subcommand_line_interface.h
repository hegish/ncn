#ifndef subcommand_line_interface_7EA60987_1DCA_4178_9D9B_7DBFF4A8E60F
#define subcommand_line_interface_7EA60987_1DCA_4178_9D9B_7DBFF4A8E60F

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>

// see https://stackoverflow.com/a/1008289 for guidance on the singleton implementation
class Subcommand
{
public:
   
   static void ensure_args(const size_t expected_arg_count, const std::vector<std::string> actual_args);
   
   typedef int(*CMD_FUNCTION)(const std::vector<std::string>);
   
   static Subcommand& instance()
   {
      static Subcommand instance_;
      return instance_;
   }
   Subcommand(Subcommand const&) = delete;
   void operator=(Subcommand const&) = delete;

   void add(const std::string cmdname, CMD_FUNCTION cmdptr);
   int execute(int argc, const char * argv[]);
   
private:
   
   Subcommand()
   : commands()
   {}
   
   std::map<std::string, CMD_FUNCTION> commands;
};

#endif

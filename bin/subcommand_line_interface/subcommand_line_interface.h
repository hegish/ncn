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
   
   typedef int(*CMD_FUNCTION)(const std::vector<std::string>);
   
   static Subcommand& instance()
   {
      static Subcommand instance_;
      return instance_;
   }
   Subcommand(Subcommand const&) = delete;
   void operator=(Subcommand const&) = delete;

   void add(const std::string cmdname, CMD_FUNCTION cmdptr)
   {
      std::pair<std::map<std::string, CMD_FUNCTION>::iterator,bool> return_pair;
      return_pair = commands.insert( std::map< std::string, CMD_FUNCTION >::value_type(cmdname, cmdptr) );
      if(return_pair.second == false)
      {
         std::stringstream msg;
         msg << __FILE__ << ":" << __LINE__ <<" duplicate sub-command: <"<<cmdname<<">";
         throw std::runtime_error(msg.str());
      }
   }
   
   int execute(int argc, const char * argv[])
   {
      std::vector<std::string> args(argv+1, argv+argc); // without argv[0], i.e. the binary name
      if(args.size() > 0)
      {
         std::string cmdname = args[0];
         std::vector<std::string> subargs(args.begin()+1, args.end());
         
         std::map<std::string, CMD_FUNCTION>::iterator it = commands.find(cmdname);
         if(it != commands.end())
         {
            CMD_FUNCTION cmdptr = it->second;
            return cmdptr(subargs);
         }
         else
         {
            std::stringstream msg;
            msg << __FILE__ << ":" << __LINE__ <<" unknown sub-command: <"<<cmdname<<">";
            throw std::runtime_error(msg.str());
         }
      }
      else
      {
         std::stringstream msg;
         msg<<"=== known sub-commands:";
         for(const auto &pair : commands)
            msg<<"\n"<<pair.first;
         std::cout<<msg.str()<<"\n==="<<std::endl;
         return 0;
      }
   }
   
private:
   
   Subcommand()
   : commands()
   {}
   
   std::map<std::string, CMD_FUNCTION> commands;
};

#endif

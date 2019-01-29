#include "subcommand_line_interface.h"

using namespace std;

void Subcommand::add(const std::string cmdname, CMD_FUNCTION cmdptr)
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


int Subcommand::execute(int argc, const char * argv[])
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

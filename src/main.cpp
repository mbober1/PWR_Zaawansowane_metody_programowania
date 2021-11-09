#include <sstream> 
#include <cassert>
#include "MobileObj.hh"
#include "InterpProgram.hpp"
#include "xmlinterp.hh"
#include "Configuration.hh"


int main()
{
  InterpProgram program;
  Set4LibInterf lib_set;

  Configuration config;

  if (false == read_file("config/config.xml", config))
  {
    std::cerr << "Błąd ładowania XMLa" << std::endl;
    return 1;
  }
  else
  {
    std::vector<std::string> lib_list = config.get_lib_list();

    for (size_t i = 0; i < lib_list.size(); i++)
    {
      lib_set.add_lib(lib_list.at(i));
    }
    
  }



  if (true == program.exec_program("commands", lib_set))
  {
    std::cerr << "Program pomyślnie zakończył pracę" << std::endl;
    return 0;
  }
  else
  {
    std::cerr << "Program napotkał błąd" << std::endl;
    return 1;
  }
}



#include <sstream> 
#include <cassert>
#include "MobileObj.hh"
#include "InterpProgram.hpp"
#include "xmlinterp.hh"
#include "Configuration.hh"
#include "sender.hpp"


int main()
{
  Configuration config; // stwórz konfigurację

  if (false == read_file("config/config.xml", config))  // odczytaj konfigurację
  {
    std::cerr << "Błąd ładowania XMLa" << std::endl;
    return 1;
  }


  std::vector<std::string> lib_list = config.get_lib_list();  // odczytaj listę bibliotek
  Set4LibInterf lib_set;

  for (size_t i = 0; i < lib_list.size(); i++) // załaduj odczytane biblioteki
  {
    lib_set.add_lib(lib_list.at(i));
  }
  

  Set_MobileObjs obj_list = config.get_obj_list(); // odczytaj listę obiektów
  InterpProgram program(obj_list);
  
  
  if (true == program.exec_program("commands", lib_set)) // wykonaj program
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
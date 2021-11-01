#include <sstream> 
#include <cassert>
#include "MobileObj.hh"
#include "utils.hpp"
#include "Set4LibInterf.hpp"

using namespace std;


int main()
{
  Set4LibInterf lib_set;

  istringstream iss;
  exec_preprocesor("commands", iss);
  std::string cmd_name;
  std::string object_name;

  while (iss >> cmd_name)
  {
    iss >> object_name;
    cout << "Obiekt: " << object_name << ", Komenda: " << cmd_name << endl;

    auto it = lib_set.get(cmd_name);

    if (it == lib_set.not_exist())
    {
      cout << "Nie znaleziono komendy: " << cmd_name << endl;
      return false;
    }
    
    auto cmd = it->second->create_cmd();

    if(false == cmd->ReadParams(iss))
    {
      cout << "Błąd czytania parametrów" << endl;
      delete cmd;
      return false;
    }

    cmd->PrintCmd();
  }
}

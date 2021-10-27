#include <iostream>
#include <sstream> 
#include <cassert>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "LibInterf.hpp"
#include "utils.hpp"
#include "Set4LibInterf.hpp"

using namespace std;

void exec_cmd(LibInterf &library, std::string cmd_name)
{
  void *new_cmd = library.cmd_list["CreateCmd"];

  if(nullptr != new_cmd)
  {
    Interp4Command *(*create_cmd)(void);
    create_cmd = *reinterpret_cast<Interp4Command* (**)(void)>(&new_cmd);
    Interp4Command *cmd_pointer = create_cmd();
    std::cout << cmd_pointer->GetCmdName() << std::endl;
    delete cmd_pointer;
  }
}

int main()
{
  Set4LibInterf lib_set;

  istringstream iss;
  exec_preprocesor("commands", iss);
  std::string cmd_name;
  std::string object_name;

  iss >> cmd_name;
  cout << cmd_name << endl;

  auto it = lib_set.get(cmd_name);

  if (it == lib_set.NOT_FOUND)
  {
    cout << "Nie znaleziono komendy: " << cmd_name << endl;
    return false;
  }
  

  Interp4Command *cmd = it->second->create_cmd();

  // if(false == cmd->ReadParams(iss))
  // {
  //   // cout << "Błąd czytania parametrów" << endl;
  //   // delete cmd;
  //   // return false;
  // }

  // cmd->PrintCmd();
}

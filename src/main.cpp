#include <iostream>
#include <sstream> 
#include <cassert>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "LibInterf.hpp"

using namespace std;



int main()
{

  LibInterf move_lib("libInterp4Move.so");
  move_lib.add_cmd("CreateCmd");

  LibInterf set_lib("libInterp4Set.so");
  set_lib.add_cmd("CreateCmd");

  LibInterf rotate_lib("libInterp4Rotate.so");
  rotate_lib.add_cmd("CreateCmd");

  LibInterf pause_lib("libInterp4Pause.so");
  pause_lib.add_cmd("CreateCmd");
  


  // void *pFunMove = dlsym(pLibHnd_Move,"CreateCmd");
  // void *pFunSet = dlsym(pLibHnd_Set,"CreateCmd");

  // if (check_fun(pFunMove, "CreateCmd")) return 1;
  // if (check_fun(pFunSet, "CreateCmd"))  return 1;


  // Interp4Command *(*pCreateCmd_Move)(void);
  // Interp4Command *(*pCreateCmd_Set)(void);

  // pCreateCmd_Move = *reinterpret_cast<Interp4Command* (**)(void)>(&pFunMove);
  // pCreateCmd_Set = *reinterpret_cast<Interp4Command* (**)(void)>(&pFunSet);


  // Interp4Command *move = pCreateCmd_Move();
  // Interp4Command *set = pCreateCmd_Set();

  // cout << endl;

  // cout << "Nazwa: " << move->GetCmdName() << endl;
  // cout << "Syntax: ";
  // move->PrintSyntax();
  // cout << "Komenda: ";
  // move->PrintCmd();


  // cout << endl;
  // cout << "Nazwa: " << set->GetCmdName() << endl;
  // cout << "Syntax: ";
  // set->PrintSyntax();
  // cout << "Komenda: ";
  // set->PrintCmd();

  // delete move;
  // delete set;

  // dlclose(pLibHnd_Move);


  // istringstream iss;
  // exec_preprocesor("commands", iss);
  // cout << endl << "Czytanie z pliku" << endl << endl << iss.str();

}

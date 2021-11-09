#pragma once
#include <sstream> 
#include "Set4LibInterf.hpp"
#include "Scene.hpp"

#define LINE_SIZE 500



class InterpProgram
{
private:
  Scene *scene;
  bool exec_preprocesor(const std::string &name, std::istringstream &stream);

public:
  InterpProgram(Set_MobileObjs &obj_list);
  ~InterpProgram();
  bool exec_program(const std::string &filename, Set4LibInterf &lib_set);

};

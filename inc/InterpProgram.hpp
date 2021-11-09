#pragma once
#include <sstream> 
#include "Set4LibInterf.hpp"
#include "Scene.hpp"

#define LINE_SIZE 500



class InterpProgram
{
private:
  Scene scene;
  bool exec_preprocesor(std::string name, std::istringstream &stream);

public:
  InterpProgram();
  ~InterpProgram();
  bool exec_program(std::string filename, Set4LibInterf &lib_set);

};

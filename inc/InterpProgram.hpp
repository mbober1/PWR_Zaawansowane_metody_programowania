#pragma once
#include <sstream> 
#include "Set4LibInterf.hpp"
#include "Scene.hpp"
#include "sender.hpp"

#define LINE_SIZE 500


/*!
 * \brief Przechowuje informacje o scenie i połączeniu
 *
 *  Przechowuje informacje o scenie i połączeniu.
 */
class InterpProgram
{
private:
  Scene *scene;
  Sender *client;
  bool exec_preprocesor(const std::string &name, std::istringstream &stream);
  void init_objects();

public:
  InterpProgram(Set_MobileObjs &obj_list);
  ~InterpProgram();
  bool exec_program(const std::string &filename, Set4LibInterf &lib_set);

};

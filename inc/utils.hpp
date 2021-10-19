#include <iostream>
#include <sstream>

#define LINE_SIZE 500


bool check_lib(void* lib_handler, std::string name);
bool check_fun(void* fun_handler, std::string name);
bool exec_preprocesor(std::string name, std::istringstream &stream);

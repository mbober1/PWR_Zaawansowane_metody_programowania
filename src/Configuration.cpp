#include "Configuration.hh"


void Configuration::add_lib(const std::string &lib_name) 
{
  this->lib_list.push_back(lib_name);
}

std::vector<std::string> & Configuration::get_lib_list() 
{
  return this->lib_list;
}

Set_MobileObjs & Configuration::get_obj_list() 
{
  return this->obj_list;
}

void Configuration::add_mobile_obj(const std::string obj_name) 
{
  // this->obj_list
}
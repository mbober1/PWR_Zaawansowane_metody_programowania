#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <vector>
#include "Scene.hpp"


class Configuration {
  std::vector<std::string> lib_list;
  Set_MobileObjs obj_list;

public:
  void add_lib(const std::string &lib_name);
  void add_mobile_obj(const std::string &obj_name, const Vector3D &Scale, const std::string RGB);
  std::vector<std::string> & get_lib_list();
  Set_MobileObjs & get_obj_list();
};


#endif

#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <vector>
#include "Scene.hpp"

/*!
 * \brief Wczytuje zdefiniowaną konfiguarcję
 *
 *  Przechowuje informacje o startowej konfiguracji
 */
class Configuration {
  std::vector<std::string> lib_list;
  Set_MobileObjs obj_list;

public:
  void add_lib(const std::string &lib_name);
  void add_mobile_obj(const std::string &Name, const Vector3D &Shift, const Vector3D &Scale, const Vector3D &Rot, const Vector3D &Trans, const std::string RGB);
  std::vector<std::string> & get_lib_list();
  Set_MobileObjs & get_obj_list();
};


#endif

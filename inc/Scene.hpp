#pragma once
#include <map>
#include <string>
#include <memory>
#include <vector>
#include "MobileObj.hh"
#include "AccessControl.hh"

typedef std::map<std::string, std::shared_ptr<MobileObj>> Set_MobileObjs;
typedef std::shared_ptr<MobileObj> Object_ptr;



/*!
 * \brief Interfejs do zarządzania obiektami na scenie. 
 *
 *  Przechowuje obiekty.
 */
class Scene : public AccessControl 
{
private:
  Set_MobileObjs &obj_list;

public:
  Scene(Set_MobileObjs &obj_list);
  ~Scene();

  Object_ptr FindMobileObj(std::string name);
  void add_object(std::string name);
  std::vector<std::string> get_objects_names();
  std::vector<Object_ptr> get_objects_ptrs();
};

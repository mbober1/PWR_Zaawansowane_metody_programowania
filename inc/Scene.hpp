#pragma once
#include <map>
#include <string>
#include <memory>
#include "MobileObj.hh"

typedef std::map<std::string, std::shared_ptr<MobileObj>> Set_MobileObjs;
typedef std::shared_ptr<MobileObj> Object_ptr;
class Scene
{
private:
  Set_MobileObjs &obj_list;

public:
  Scene(Set_MobileObjs &obj_list);
  ~Scene();

  Object_ptr FindMobileObj(std::string name);
  void add_object(std::string name);
};

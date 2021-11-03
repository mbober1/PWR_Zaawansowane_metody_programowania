#pragma once
#include <map>
#include <string>
#include <memory>
#include "MobileObj.hh"

typedef std::map<std::string, std::shared_ptr<MobileObj>> Set_MobileObjs;

class Scene
{
private:
  Set_MobileObjs obj_list;

public:
  Scene(/* args */);
  ~Scene();

  std::shared_ptr<MobileObj> FindMobileObj(std::string name);
  void add_object(std::string name);
};

#include "Scene.hpp"

Scene::Scene() {}

Scene::~Scene() {}

std::shared_ptr<MobileObj> Scene::FindMobileObj(std::string name) 
{
  auto it = this->obj_list.find(name);

  if (it == obj_list.end()) 
  {
    return nullptr;
  }
  else
  {
    return (it->second);
  }
}

void Scene::add_object(std::string name) 
{
  std::shared_ptr<MobileObj> obj_ptr = std::make_shared<MobileObj>();
  this->obj_list.insert({name, obj_ptr});
}

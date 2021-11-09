#include "Scene.hpp"

Scene::Scene(Set_MobileObjs &obj_list) : obj_list(obj_list) 
{
  Set_MobileObjs::iterator it;

  std::cerr << "Stworzono nową scenę!" << std::endl;
  std::cerr << "Lista obiektów:" << std::endl;

  for (it = obj_list.begin(); it != obj_list.end(); it++)
  {
    std::cerr << "  " << it->first << std::endl;
  }

}

Scene::~Scene() {}

Object_ptr Scene::FindMobileObj(std::string name) 
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
  Object_ptr obj_ptr = std::make_shared<MobileObj>();
  this->obj_list.insert({name, obj_ptr});
}

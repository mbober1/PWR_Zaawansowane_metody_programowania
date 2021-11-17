#include "Scene.hpp"


/*!
* \brief Inicjalizuje obiekt listą obiektów mobilnych.
*/
Scene::Scene(Set_MobileObjs &obj_list) : obj_list(obj_list) 
{
  Set_MobileObjs::iterator it;

  std::cerr << "Stworzono nową scenę!" << std::endl;
  std::cerr << "Lista obiektów:" << std::endl;

  auto objects = this->get_objects_names();

  for (size_t i = 0; i < objects.size(); ++i)
  {
    std::cerr << "  " << objects.at(i) << std::endl;
  }

}


/*!
* \brief Deinicjalizuje obiekt.
*/
Scene::~Scene() {}


/*!
* \brief Szuka obiektu na scenie po nazwie.
* \param[in] name - nazwa szukanego obiektu.
*/
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


/*!
* \brief Dodaje obiekt do sceny.
* \param[in] name - nazwa dodawanego obiektu.
*/
void Scene::add_object(std::string name) 
{
  Object_ptr obj_ptr = std::make_shared<MobileObj>();
  this->obj_list.insert({name, obj_ptr});
}


/*!
* \brief Zwraca nazwy wszystkich obiektów na scenie.
* \return Wektor nazw obiektów.
*/
std::vector<std::string> Scene::get_objects_names() {
  std::vector<std::string> result;
  Set_MobileObjs::iterator it;

  for (it = obj_list.begin(); it != obj_list.end(); it++)
  {
    result.push_back(it->first);
  }

  return result;
}


/*!
* \brief Zwraca wskaźniki wszystkich obiektów na scenie.
* \return Wektor wskaźników obiektów.
*/
std::vector<Object_ptr> Scene::get_objects_ptrs()
{
  std::vector<Object_ptr> result;
  Set_MobileObjs::iterator it;

  for (it = obj_list.begin(); it != obj_list.end(); it++)
  {
    result.push_back(it->second);
  }

  return result;
}

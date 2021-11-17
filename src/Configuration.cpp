#include "Configuration.hh"

/*!
 * \brief Dodaj bilbiotekę do listy
 */
void Configuration::add_lib(const std::string &lib_name) 
{
  this->lib_list.push_back(lib_name);
}

/*!
 * \brief Pobierz listę nazw dostępnych bibliotek w postaci wektora.
 * \return Zwraca referencję na listę nazw bibliotek.
 */
std::vector<std::string> & Configuration::get_lib_list() 
{
  return this->lib_list;
}

/*!
 * \brief Pobierz listę dostępnych bibliotek w postaci mapy
 * \return Zwraca mapę bibliotek.
 */
Set_MobileObjs & Configuration::get_obj_list() 
{
  return this->obj_list;
}

/*!
 * \brief Dodaj obiekt do listy
 */
void Configuration::add_mobile_obj(const std::string &obj_name, const Vector3D &Scale, const std::string RGB) 
{
  Object_ptr new_object = std::make_shared<MobileObj>();

  new_object->SetName(obj_name.c_str());
  new_object->SetScale(Scale);
  new_object->SetColour(RGB);

  this->obj_list.insert({obj_name, new_object});
}
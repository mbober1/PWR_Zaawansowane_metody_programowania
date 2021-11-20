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
void Configuration::add_mobile_obj(const std::string &Name, const Vector3D &Shift, const Vector3D &Scale, const Vector3D &Rot, const Vector3D &Trans, const std::string RGB) 
{
  Object_ptr new_object = std::make_shared<MobileObj>();

  new_object->SetName(Name.c_str());
  new_object->SetPosition_m(Trans);
  new_object->SetScale(Scale);
  new_object->SetShift(Shift);
  new_object->SetAng_Pitch_deg(Rot[0]);
  new_object->SetAng_Roll_deg(Rot[1]);
  new_object->SetAng_Yaw_deg(Rot[2]);
  new_object->SetColour(RGB);

  this->obj_list.insert({Name, new_object});
}
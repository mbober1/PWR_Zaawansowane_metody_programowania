#include "Set4LibInterf.hpp"

/*!
 * \brief Konstruktor Set4LibInterf.
 */
Set4LibInterf::Set4LibInterf() {}


/*!
 * \brief Destruktor Set4LibInterf.
 */
Set4LibInterf::~Set4LibInterf() {}

  
/*!
 * \brief Dodawanie biblioteki o podanej nazwie.
 */
void Set4LibInterf::add_lib(std::string path) 
{
  std::shared_ptr<LibInterf> lib_ptr = std::make_shared<LibInterf>(path);
  this->lib_map.insert({lib_ptr->name, lib_ptr});
}

  
/*!
 * \brief Zwraca koniec mapy.
 */
LibInterfMap::iterator Set4LibInterf::not_exist() 
{
  return this->lib_map.end();
}

  
/*!
 * \brief Szuka biblioteki po nazwie.
 * \return Zwraca wskaźnik na znalezioną bibliotekę.
 */
std::shared_ptr<LibInterf> Set4LibInterf::find(std::string name) {
  auto it = this->lib_map.find(name);

  if (it == lib_map.end()) 
  {
    return nullptr;
  }
  else
  {
    return (it->second);
  }
}

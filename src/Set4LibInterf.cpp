#include "Set4LibInterf.hpp"

/*!
 * \brief Konstruktor Set4LibInterf
 */
Set4LibInterf::Set4LibInterf()
{
  add_lib("libs/libInterp4Move.so");
  add_lib("libs/libInterp4Set.so");
  add_lib("libs/libInterp4Rotate.so");
  add_lib("libs/libInterp4Pause.so");
}


/*!
 * \brief Destruktor Set4LibInterf
 */
Set4LibInterf::~Set4LibInterf() {}

  
// /*!
//  * \brief Zwraca iterator na obiekt o podanej nazwie
//  *
//  * \return Zwraca iterator na obiekt
//  */
// inline LibInterfMap::const_iterator Set4LibInterf::get(std::string name) 
// {
//   return lib_map.find(name);
// }

  
/*!
 * \brief Dodawanie biblioteki o podanej nazwie
 */
void Set4LibInterf::add_lib(std::string path) 
{
  std::shared_ptr<LibInterf> lib_ptr = std::make_shared<LibInterf>(path);
  this->lib_map.insert({lib_ptr->name, lib_ptr});
}

  
/*!
 * \brief Zwraca koniec mapy
 */
LibInterfMap::iterator Set4LibInterf::not_exist() 
{
  return this->lib_map.end();
}

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

#pragma once
#include <map>
#include "LibInterf.hpp"
#include <memory>

#define NOT_FOUND lib_map.end()
typedef std::map<std::string, std::shared_ptr<LibInterf>> LibInterfMap;
class Set4LibInterf
{
private:
    
public:
    Set4LibInterf(/* args */);
    ~Set4LibInterf();
    LibInterfMap::const_iterator get(std::string name);
    LibInterfMap lib_map;
};

Set4LibInterf::Set4LibInterf(/* args */)
{
  std::shared_ptr<LibInterf> move_ptr = std::make_shared<LibInterf>("libs/libInterp4Move.so");
  std::shared_ptr<LibInterf> set_ptr = std::make_shared<LibInterf>("libs/libInterp4Set.so");
  std::shared_ptr<LibInterf> rotate_ptr = std::make_shared<LibInterf>("libs/libInterp4Rotate.so");
  std::shared_ptr<LibInterf> pause_ptr = std::make_shared<LibInterf>("libs/libInterp4Pause.so");

  this->lib_map.insert({move_ptr->name, move_ptr});
  this->lib_map.insert({"Set", set_ptr});
  this->lib_map.insert({"Rotate", rotate_ptr});
  this->lib_map.insert({"Pause", pause_ptr});
}

Set4LibInterf::~Set4LibInterf()
{
}

inline LibInterfMap::const_iterator Set4LibInterf::get(std::string name) 
{
  return lib_map.find(name);
}

#pragma once
#include <map>
#include "LibInterf.hpp"
#include <memory>

typedef std::map<std::string, std::shared_ptr<LibInterf>> LibInterfMap;
class Set4LibInterf
{
private:
    LibInterfMap lib_map;
    
public:
    Set4LibInterf();
    ~Set4LibInterf();
    LibInterfMap::const_iterator get(std::string name);
    void add_lib(std::string path);
    LibInterfMap::iterator not_exist();
};

Set4LibInterf::Set4LibInterf()
{
  add_lib("libs/libInterp4Move.so");
  add_lib("libs/libInterp4Set.so");
  add_lib("libs/libInterp4Rotate.so");
  add_lib("libs/libInterp4Pause.so");
}

Set4LibInterf::~Set4LibInterf() {}

inline LibInterfMap::const_iterator Set4LibInterf::get(std::string name) 
{
  return lib_map.find(name);
}

inline void Set4LibInterf::add_lib(std::string path) 
{
  std::shared_ptr<LibInterf> lib_ptr = std::make_shared<LibInterf>(path);
  this->lib_map.insert({lib_ptr->name, lib_ptr});
}

inline LibInterfMap::iterator Set4LibInterf::not_exist() 
{
  return this->lib_map.end();
}

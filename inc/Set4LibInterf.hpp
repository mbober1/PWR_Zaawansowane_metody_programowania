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
  LibInterf move_lib("libs/libInterp4Move.so");
  LibInterf set_lib("libs/libInterp4Set.so");
  LibInterf rotate_lib("libs/libInterp4Rotate.so");
  LibInterf pause_lib("libs/libInterp4Pause.so");

  auto fdsd = move_lib.create_cmd();
  std::cout << fdsd->GetCmdName() <<  std::endl;

  std::shared_ptr<LibInterf> move_ptr = std::make_shared<LibInterf>(move_lib);
  std::shared_ptr<LibInterf> set_ptr = std::make_shared<LibInterf>(set_lib);
  std::shared_ptr<LibInterf> rotate_ptr = std::make_shared<LibInterf>(rotate_lib);
  std::shared_ptr<LibInterf> pause_ptr = std::make_shared<LibInterf>(pause_lib);

  auto dupa = move_ptr.get();
  auto ddd = dupa->create_cmd();
  std::cout << ddd->GetCmdName() <<  std::endl;

  this->lib_map.insert({"Move", move_ptr});
  this->lib_map.insert({"Set", set_ptr});
  this->lib_map.insert({"Rotate", rotate_ptr});
  this->lib_map.insert({"Pause", pause_ptr});

  auto dddddd = get("Move");
  auto tttt = dddddd->second->create_cmd();

  std::cout << tttt->GetCmdName() <<  std::endl;
}

Set4LibInterf::~Set4LibInterf()
{
}

inline LibInterfMap::const_iterator Set4LibInterf::get(std::string name) 
{
  return lib_map.find(name);
}

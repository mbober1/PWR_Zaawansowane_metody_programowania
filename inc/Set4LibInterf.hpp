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
    void add_lib(std::string path);
    LibInterfMap::iterator not_exist();
    std::shared_ptr<LibInterf> find(std::string name);
};

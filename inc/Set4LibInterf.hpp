#pragma once
#include <map>
#include "LibInterf.hpp"
#include <memory>

class Set4LibInterf
{
private:
    std::map<std::string, std::shared_ptr<LibInterf>> lib_map;
public:
    Set4LibInterf(/* args */);
    ~Set4LibInterf();
};

Set4LibInterf::Set4LibInterf(/* args */)
{
}

Set4LibInterf::~Set4LibInterf()
{
}

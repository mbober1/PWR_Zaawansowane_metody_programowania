#pragma once
#include <string>
#include <map>

class LibInterf
{
private:
    void* handler;
    std::map<std::string, void*> cmd_list;

public:
    LibInterf(std::string path);
    ~LibInterf();
    bool add_cmd(std::string cmd_name);
};


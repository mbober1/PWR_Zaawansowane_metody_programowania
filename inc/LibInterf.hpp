#pragma once
#include <string>
#include <map>
#include "Interp4Command.hh"

class LibInterf
{
private:
    void* handler; // uchwyt do biblioteki

public:
    LibInterf(std::string path);
    ~LibInterf();
    bool init_lib(std::string cmd_name);
    bool load_lib(std::string path);

    std::map<std::string, void*> cmd_list; // lista dostępnych komend
    Interp4Command *(*create_cmd)(void);
};


#include "LibInterf.hpp"
#include <dlfcn.h>
#include <iostream>


LibInterf::LibInterf(std::string path)
{
    load_lib(path);
    init_lib();
}

LibInterf::~LibInterf()
{
    dlclose(this->handler);
}


bool LibInterf::init_lib()
{
    void *new_cmd = dlsym(this->handler, "CreateCmd");

    if (nullptr == new_cmd) 
    {
        std::cerr << "Brak funkcji: CreateCmd" << std::endl;
        return false;
    }

    create_cmd = reinterpret_cast<Interp4Command* (*)(void)>(new_cmd);
    Interp4Command* interpreted_cmd = create_cmd();
    this->name = interpreted_cmd->GetCmdName();
    delete interpreted_cmd;
    return true;
}

bool LibInterf::load_lib(std::string path) {
    this->handler = dlopen(path.c_str(), RTLD_LAZY);

    if (nullptr == this->handler) 
    {
        std::cerr << "Brak biblioteki: " << path << std::endl;
        return false;
    }
    else
    {
        std::cout << "Biblioteka " << path << " załadowana" << std::endl;
        return true;
    }
}

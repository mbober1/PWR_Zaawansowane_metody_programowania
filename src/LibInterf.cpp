#include "LibInterf.hpp"
#include <dlfcn.h>
#include <iostream>


LibInterf::LibInterf(std::string path)
{
    load_lib(path);
    init_lib("CreateCmd");
}

LibInterf::~LibInterf()
{
    dlclose(this->handler);
}


bool LibInterf::init_lib(std::string cmd_name)
{
    void *new_cmd = dlsym(this->handler, cmd_name.c_str());

    if (nullptr == new_cmd) 
    {
        std::cerr << "Brak funkcji: " << cmd_name << std::endl;
        return false;
    }
    else
    {
        std::cout << "Funkcja " << cmd_name << " znaleziona" << std::endl;
        this->cmd_list.insert({cmd_name, new_cmd});
        return true;
    }

    create_cmd = *reinterpret_cast<Interp4Command* (**)(void)>(&new_cmd);
    Interp4Command * interpreted_cmd = create_cmd();
    std::cout << interpreted_cmd->GetCmdName();
    delete interpreted_cmd;
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

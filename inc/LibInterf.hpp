#pragma once
#include <string>
#include <map>
#include "Interp4Command.hh"


/*!
 * \brief Interfejs ładowania wtyczek 
 *
 *  Przechowuje uchwyt i zarządza biblioteką 
 */
class LibInterf
{
private:
    void* handler; // uchwyt do biblioteki

public:
    LibInterf(std::string path);
    ~LibInterf();
    bool init_lib();
    bool load_lib(std::string path);

    std::string name;

    // std::map<std::string, void*> cmd_list; // lista dostępnych komend
    Interp4Command *(*create_cmd)(void);
};


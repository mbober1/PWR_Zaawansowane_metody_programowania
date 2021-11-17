#include "InterpProgram.hpp"
#include "Set4LibInterf.hpp"
#include <unistd.h>


/*!
* \brief Inicjalizuje obiekt listą obiektów mobilnych.
*/
InterpProgram::InterpProgram(Set_MobileObjs &obj_list)
{
  this->scene = new Scene(obj_list);
}


/*!
* \brief Deinicjalizuje obiekt.
*/
InterpProgram::~InterpProgram() 
{
  if (nullptr != this->client)
  {
    delete this->client;
  }

  if (nullptr != this->scene)
  {
    delete this->scene;
  }
}

  
/*!
 * \brief Uruchomienie wykonywania głównej pętli programu.
 * \return Zwraca true gdy operacja się powiedzie
 */
bool InterpProgram::exec_program(const std::string &filename, Set4LibInterf &lib_set)
{
  std::istringstream iss;
  this->exec_preprocesor(filename, iss);
  std::string cmd_name;
  std::string object_name;

  this->client = new Sender(this->scene);

  if (false == this->client->open_connection())
  {
    std::cerr << "Nie można otworzyć połączenia!" << std::endl;
    return false;
  }


  ////////////////////////////////////////////
  const char *sConfigCmds =
"Clear\n"
"AddObj Name=Podstawa RGB=(20,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,20) Trans_m=(-1,3,0)\n"
"AddObj Name=Podstawa.Ramie1 RGB=(200,0,0) Scale=(3,3,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
"AddObj Name=Podstawa.Ramie1.Ramie2 RGB=(100,200,0) Scale=(2,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n";      
client->send(sConfigCmds);
/////////////////////////////////////////////


  while (iss >> cmd_name)
  {
    iss >> object_name; // wczytaj nazwę obiektu

    auto library = lib_set.find(cmd_name); // wyszukaj plugin

    if (nullptr == library)
    {
      std::cout << "Nie znaleziono komendy: " << cmd_name << std::endl;
      return false;
    }

    auto cmd = library->create_cmd(); // utwórz interpreter

    if(false == cmd->ReadParams(iss)) // wczytaj parametry
    {
      std::cout << "Błąd czytania parametrów" << std::endl;
      delete cmd;
      return false;
    }

    
    auto object = scene->FindMobileObj(object_name); // znajdź obiekt

    if (nullptr == object)
    {
      std::cout << "Nie można znaleźć obiektu o nazwie: " << object_name << std::endl;
      delete cmd;
      return false;
    }

    cmd->ExecCmd(object.get(), 0); // wykonaj operację

    // scene->LockAccess();
    // scene->MarkChange();
    // scene->UnlockAccess();
    // usleep(300000);
    

    delete cmd;
  }

  return true;
}

  
/*!
 * \brief Uruchomienie preprocesora
 * \return Zwraca true gdy operacja się powiedzie
 */
bool InterpProgram::exec_preprocesor(const std::string &name, std::istringstream &stream)
{
  bool result = false;
  std::string cmd = "cpp -P ";
  char buffer[LINE_SIZE];
  std::ostringstream output;

  FILE* pipe = popen((cmd + name).c_str(), "r");

  if (nullptr != pipe)
  {
    while (fgets(buffer, LINE_SIZE, pipe))
    {
      output << buffer;
    }

    stream.str(output.str());
    result = (pclose(pipe) == 0);
  }

  return result;
}
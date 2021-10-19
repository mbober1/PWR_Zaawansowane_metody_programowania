#include "utils.hpp"


bool check_lib(void* lib_handler, std::string name)
{
  if (nullptr == lib_handler) 
  {
    std::cerr << "Brak biblioteki: " << name << std::endl;
    return true;
  }
  else
  {
    std::cout << "Biblioteka " << name << " załadowana" << std::endl;
    return false;
  }
}

bool check_fun(void* fun_handler, std::string name)
{
  if (nullptr == fun_handler) 
  {
    std::cerr << "Brak funkcji: " << name << std::endl;
    return true;
  }
  else
  {
    std::cout << "Funkcja " << name << " znaleziona" << std::endl;
    return false;
  }
}


bool exec_preprocesor(std::string name, std::istringstream &stream)
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
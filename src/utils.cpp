#include "utils.hpp"



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
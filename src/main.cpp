#include <sstream> 
#include <cassert>
#include "MobileObj.hh"
#include "InterpProgram.hpp"

using namespace std;


int main()
{
  InterpProgram program;

  if (true == program.exec_program("commands"))
  {
    std::cout << "Program pomyślnie zakończył pracę" << std::endl;
  }
  else
  {
    std::cout << "Program napotkał błąd" << std::endl;
  }


}

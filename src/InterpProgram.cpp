#include "InterpProgram.hpp"
#include "Set4LibInterf.hpp"

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

  this->init_objects();

  while (iss >> cmd_name)
  {
    std::vector<std::thread*> threads_list;

    while (!(cmd_name == "Begin_Parallel_Actions"))
    {
      iss >> cmd_name;
    }

    while (!(cmd_name == "End_Parallel_Actions"))
    {
      iss >> cmd_name;    // wczytaj wykonywaną komendę

      if (cmd_name == "End_Parallel_Actions")
      {
        break;
      }

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

      std::thread* new_thread = new std::thread(&Interp4Command::ExecCmd, cmd, object.get(), scene);
      threads_list.push_back(new_thread);
    }

    for (auto thread_object : threads_list) // czekaj na zakończenie wszystkich zadań
    {
      thread_object->join();
      delete thread_object;
    }
    
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


/*!
 * \brief Inicjalizuje obiekty na scenie
 */
void InterpProgram::init_objects()
{
  auto objects_list = this->scene->get_objects_ptrs();

  for (auto object_ptr : objects_list)
  {
    auto object = object_ptr.get();

    std::string message = "AddObj";
    message += object->GetStateDesc();

    this->client->send(message.c_str());
  }
}
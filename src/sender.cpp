#include "sender.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "AccessControl.hh"
#include "Port.hh"
#include <string.h>


/*!
 * \brief Funkcja jest treścią wątku komunikacyjnego
 * 
 * Funkcja jest treścią wątku komunikacyjnego.
 * \param[in] sender - odpowiada za śledenie zmian na scenie 
 *                      i przesyłanie do serwera graficznego
 *                      aktualnego stanu sceny, gdy uległ on zmianie.
 */
void communication_thread(Sender *sender)
{
  sender->Watching_and_Sending();
}


/*!
* \brief Inicjalizuje obiekt deskryptorem gniazda i wskaźnikiem
*        na scenę, na zmianę stanu które będzie ten obiekt reagował.
*/
Sender::Sender(Scene *scene): scene(scene), connected(false)
{
  this->client_thread = std::thread(communication_thread, this);
}


/*!
* \brief Deinicjalizuje obiekt, zamyka bezpiecznie połączenie oraz gniazdo.
*/
Sender::~Sender()
{
  if (true == this->connected)
  {
    this->send("Close\n");
  }
  
  this->CancelCountinueLooping();
  this->client_thread.join();
  close(_Socket);
}


/*!
* \brief Sprawdza, czy pętla wątku może być wykonywana.
* 
* Sprawdza, czy pętla wątku może być wykonywana.
* \retval true - pętla wątku może być nadal wykonywana.
* \retval false - w przypadku przeciwnym.
*/
bool Sender::ShouldCountinueLooping() const 
{ 
  return _ContinueLooping; 
}


/*!
* \brief Powoduje przerwanie działania pętli wątku.
*
* Powoduje przerwanie działania pętli wątku.
* \warning Reakcja na tę operację nie będize natychmiastowa.
*/  
void Sender::CancelCountinueLooping() 
{ 
  _ContinueLooping = false; 
}


/*!
* \brief Ta metoda jest de facto treścią wątku komunikacyjnego
*
* Przegląda scenę i tworzy odpowiednie polecenia, a następnie
* wysyła je do serwera.
* \param[in] Socket - deskryptor gniazda sieciowego, poprzez które
*                     wysyłane są polecenia.
*/
void Sender::Watching_and_Sending() 
{
  while (ShouldCountinueLooping()) 
  {
    if (!scene->IsChanged())
    { 
      usleep(10000); 
      continue; 
    }

    scene->LockAccess();

    auto objects_list = scene->get_objects_ptrs();


    for (auto object_ptr : objects_list)
    {
      auto object = object_ptr.get();

      std::string message = "UpdateObj";
      message += object->GetStateDesc();

      this->send(message.c_str());
      std::cerr << message.c_str();
    }
    
    scene->CancelChange();
    scene->UnlockAccess();
  }
}


/*!
 * \brief Wysyła napis do poprzez gniazdo sieciowe.
 *
 * Wysyła napis do poprzez gniazdo sieciowe.
 * \param[in] message - zawiera napis, który ma zostać wysłany poprzez
 *                    gniazdo sieciowe.
 */
int Sender::send(const char *message)
{
  ssize_t  message_len = (ssize_t) strlen(message);
  ssize_t  send_len;

  std::string debug(message, message_len);
  std::cerr << debug;

  if (true == this->connected)
  {
    while ((send_len = write(this->_Socket, message, message_len)) > 0) 
    {
      message_len -= send_len;
      message += send_len;
    }

    if (send_len < 0) 
    {
      std::cerr << "*** Blad przeslania napisu." << std::endl;
    }
  }
  else
  {
    std::cerr << "*** Blad przeslania napisu. Połącznie nie zostało otwarte." << std::endl;
  }

  return 0;
}


/*!
 * Otwiera połączenie sieciowe.
 */
bool Sender::open_connection()
{
  if (false == this->connected)
  {
    struct sockaddr_in server;

    bzero((char *)&server, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORT);

    this->_Socket = socket(AF_INET, SOCK_STREAM, 0);

    if (this->_Socket < 0) 
    {
      std::cerr << "*** Blad otwarcia gniazda." << std::endl;
      return false;
    }

    if (connect(this->_Socket,(struct sockaddr*)&server,sizeof(server)) < 0)
    {
      std::cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << std::endl;
      return false;
    }

    this->connected = true;
    return true;
  }
  else
  {
    std::cerr << "*** Blad otwarcia gniazda. Połączenie jest już nawiązane." << std::endl;
    return false;
  }
  
}
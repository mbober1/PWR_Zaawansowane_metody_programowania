#pragma once

#include "Scene.hpp"
#include <thread>
#include <unistd.h>


/*!
 * \brief Modeluje nadajnik poleceń odzwierciedlających aktualny stan sceny.
 *
 * Modeluje nadajnik poleceń odzwierciedlających aktualny stan sceny.
 * W tym celu monitoruje zmiany na scenie, a gdy je wykryje przesyła
 * informacje o aktualnej pozycji wszystkich obiektów.
 */
class Sender 
{
  /*!
  * \brief Wartość tego pola decyduje o kontynuacji wykonywania wątku.
  * 
  * Wartość tego pola decyduje o kontynuacji wykonywania wątku.
  * W przypadku wartości \p true, pętla wątku będzie wykonywana.
  * Natomiast wartość \p false powoduje przerwanie pętli.
  */
  volatile bool    _ContinueLooping = true;
  /*!
  * \brief Deskryptor gniazda sieciowego, poprzez które wysyłane są polecenia.
  */
  int             _Socket = 0;
  /*!
  * \brief Wskaźnik na scenę, które stan jest przesyłany w postaci
  *        poleceń do serwera graficzneg.
  */
  Scene          *scene = nullptr;
  std::thread client_thread;
  bool connected;

public:
  Sender(Scene *scene);
  ~Sender();
  bool ShouldCountinueLooping() const;
  void CancelCountinueLooping();
  void Watching_and_Sending();
  int send(const char *message);
  bool open_connection();
};
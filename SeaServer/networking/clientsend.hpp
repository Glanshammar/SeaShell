#ifndef SENDTOCLIENT_HPP
#define SENDTOCLIENT_HPP

#include "../../global.hpp"
void SendToClient(SOCKET clientSocket, const char* message);
void EndCom(SOCKET clientSocket);

#endif //SENDTOCLIENT_HPP

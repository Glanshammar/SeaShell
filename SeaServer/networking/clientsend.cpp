#include "clientsend.hpp"

void EndCom(SOCKET clientSocket) {
    SendToClient(clientSocket, "END_OF_COMMUNICATION");
}

void SendToClient(SOCKET clientSocket, const char* message) {
    send(clientSocket, message, strlen(message), 0);
    Sleep(1);
}
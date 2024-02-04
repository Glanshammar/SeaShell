#include "clientsend.hpp"

void SendClient(SOCKET clientSocket, const char* message) {
    send(clientSocket, message, strlen(message), 0);
    Sleep(1);
}
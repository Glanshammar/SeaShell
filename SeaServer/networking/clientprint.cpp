#include "clientprint.hpp"

void ClientPrint(SOCKET clientSocket, const char* message) {
    send(clientSocket, message, strlen(message), 0);
}
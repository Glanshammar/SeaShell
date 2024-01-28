#include "sendtoclient.hpp"

void SendToClient(SOCKET clientSocket, const char* message) {
    send(clientSocket, message, strlen(message), 0);
}
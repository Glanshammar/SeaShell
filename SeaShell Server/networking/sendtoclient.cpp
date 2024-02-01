#include "sendtoclient.hpp"

void SendResponse(SOCKET clientSocket, const char* message) {
    send(clientSocket, message, strlen(message), 0);
}
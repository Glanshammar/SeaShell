#include "../global.hpp"
#include "functions.hpp"


void HelloWorld(const SOCKET clientSocket) {
    SendToClient(clientSocket, "Hello from server!");
    SendToClient(clientSocket, "Hello from server!");
    SendToClient(clientSocket, "Hello from server!");
}
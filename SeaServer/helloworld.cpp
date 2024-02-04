#include "../global.hpp"
#include "functions.hpp"


void HelloWorld(const SOCKET clientSocket) {
    SendToClient(clientSocket, "Hello from server!");
    Sleep(2);
    SendToClient(clientSocket, "Hello from server!");
    Sleep(2);
    SendToClient(clientSocket, "Hello from server!");
    Sleep(2);
}

void CustomCommand(const SOCKET clientSocket) {
    SendToClient(clientSocket, "Custom command executed!");
}

void AnotherCommand(const SOCKET clientSocket) {
    SendToClient(clientSocket, "Another command executed!");
}
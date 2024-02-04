#include "../global.hpp"
#include "functions.hpp"


void HelloWorld(const SOCKET clientSocket) {
    SendClient(clientSocket, "Hello from server!");
    SendClient(clientSocket, "Hello from server!");
    SendClient(clientSocket, "Hello from server!");
}
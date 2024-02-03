#include "../global.hpp"
#include "functions.hpp"

// Function to handle the "HELLO" command
void HelloWorld(const SOCKET clientSocket) {
    SendToClient(clientSocket, "Hello from server!");
}

// Function to handle the "CUSTOM_COMMAND" command
void CustomCommand(const SOCKET clientSocket) {
    SendToClient(clientSocket, "Custom command executed!");
}

// Function to handle the "ANOTHER_COMMAND" command
void AnotherCommand(const SOCKET clientSocket) {
    SendToClient(clientSocket, "Another command executed!");
}
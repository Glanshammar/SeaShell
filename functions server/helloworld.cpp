#include "../global.hpp"
#include "functions.hpp"

// Function to handle the "HELLO" command
void HelloWorld(SOCKET clientSocket) {
    SendToClient(clientSocket, "Hello from server!");
    cout << "Sending hello." << endl;
}

// Function to handle the "CUSTOM_COMMAND" command
void CustomCommand(SOCKET clientSocket) {
    SendToClient(clientSocket, "Custom command executed!");
}

// Function to handle the "ANOTHER_COMMAND" command
void AnotherCommand(SOCKET clientSocket) {
    SendToClient(clientSocket, "Another command executed!");
}
#include "../global.hpp"
#include "functions.hpp"
#include <unistd.h>
#include <winsock2.h>
#include <ws2ipdef.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <functional>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

using CommandHandler = std::function<void(SOCKET)>;

std::map<std::string, CommandHandler> commandHandlers = {
    {"hello", HelloWorld},
    {"custom", CustomCommand},
    {"another", AnotherCommand}
};

void HandleCommand(const char* command, SOCKET clientSocket) {
    // Find the command in the map
    auto it = commandHandlers.find(command);

    if (it != commandHandlers.end()) {
        // Execute the corresponding function
        it->second(clientSocket);
    } else {
        std::cout << "Unknown command: " << command << std::endl;
    }
}

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        return 1;
    }

    // Create a socket
    SOCKET serverSocket = socket(AF_INET6, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket" << std::endl;
        WSACleanup();
        return 1;
    }

    // Set up server address structure
    const std::string port = "8080";
    sockaddr_in6 serverAddress{};
    serverAddress.sin6_family = AF_INET6;
    serverAddress.sin6_addr = in6addr_any;
    serverAddress.sin6_port = htons(std::stoi(port));

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Error binding socket" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Error listening for connections" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server is listening on port " << port << std::endl;

    while (true) {
        bool running = true;
        // Accept incoming connections
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Error accepting connection" << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        std::cout << "Client connected." << std::endl;

        // Receive data from the client
        char buffer[1024];
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0'; // Null-terminate the received data
            std::cout << "Received data from client: " << buffer << std::endl;

            // Handle the command
            HandleCommand(buffer, clientSocket);
        } else {
            std::cerr << "Error receiving data from client" << std::endl;
        }

        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup();

    return 0;
}
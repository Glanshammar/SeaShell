#include "../global.hpp"
#include "functions.hpp"
#include <unistd.h>
#include <ws2ipdef.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <functional>
#include <atomic>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

using CommandHandler = std::function<void(SOCKET)>;

std::map<std::string, CommandHandler> commandHandlers = {
    {"hello", HelloWorld},
    {"custom", CustomCommand},
    {"another", AnotherCommand},
};

void HandleCommand(const char* command, const SOCKET clientSocket) {
    const auto it = commandHandlers.find(command);

    if (it != commandHandlers.end()) {
        it->second(clientSocket);
    } else {
        std::cout << "Unknown command: " << command << std::endl;
        ClientPrint(clientSocket, "Unknown command.");
    }
}

std::atomic<bool> running(true);

void HandleClient(SOCKET clientSocket) {
    char buffer[1024];

    while (running.load(std::memory_order_acquire)) {
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesRead > 0) {
            buffer[bytesRead] = '\0'; // Null-terminate the received data
            std::cout << "From client: " << buffer << std::endl;

            if (strcmp(buffer, "exit") == 0) {
                std::cout << "Client requested to exit. Closing connection." << std::endl;
                break;
            }

            HandleCommand(buffer, clientSocket);
        } else if (bytesRead == 0) {
            std::cout << "Connection closed by the client." << std::endl;
            break;
        } else {
            std::cerr << "Error receiving data from client or it disconnected." << std::endl;
            break;
        }
    }

    closesocket(clientSocket);
}


int main() {
    // FreeConsole();
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
    sockaddr_in6 serverAddress{};
    serverAddress.sin6_family = AF_INET6;
    serverAddress.sin6_addr = in6addr_any;
    serverAddress.sin6_port = htons(8080); // You can change the port as needed

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


    std::cout << "Server is listening for connections on port 8080..." << std::endl;

    while (running.load()) {
        // Accept a client connection
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Error accepting client connection" << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        std::cout << "Client connected." << std::endl;

        // Handle the client in a separate thread
        std::thread(HandleClient, clientSocket).detach();
    }

    // Clean up
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
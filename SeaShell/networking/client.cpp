#include "client.hpp"
#include <ws2ipdef.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")


void ConnectToServer(const std::vector<std::string>& args, const std::vector<std::string>& options) {

    const std::string serverIP = args.empty() ? "::1" : args[0];
    const std::string serverPort = (args.size() == 2) ? args[1] : "8080";
    string serverName;
    if (serverIP == "::1") {
        serverName = "localhost";
    } else {
        serverName = serverIP;
    }

    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        return;
    }

    // Create a socket
    SOCKET clientSocket = socket(AF_INET6, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket" << std::endl;
        WSACleanup();
        return;
    }

    // Set up server address structure
    sockaddr_in6 serverAddress{};
    serverAddress.sin6_family = AF_INET6;

    // Use InetPton to convert the server IP address
    if (InetPton(AF_INET6, serverIP.c_str(), &(serverAddress.sin6_addr)) != 1) {
        std::cerr << "Error converting IP address" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return;
    }

    serverAddress.sin6_port = htons(std::stoi(serverPort));

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Error connecting to the server" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return;
    }

    std::cout << "Connected to the server." << std::endl;

    char buffer[1024];
    std::string command;

    while(true)
    {
        std::cout << "@" << serverName << " >> ";
        std::getline(std::cin, command);

        if (command.empty()) {
            continue;
        }

        if (send(clientSocket, command.c_str(), command.size(), 0) == SOCKET_ERROR) {
            std::cerr << "Error sending command" << std::endl;
            return;
        }

        if (command == "exit") {
            break;
        }

        while (true) {
            int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

            if (bytesRead > 0) {
                buffer[bytesRead] = '\0'; // Null-terminate the received Data
                std::cout << "Server response: " << buffer << std::endl;
            } else if (bytesRead == 0) {
                std::cout << "Connection closed by the server." << std::endl;
                break;  // Exit the inner loop if the server closed the connection
            } else {
                std::cerr << "Error receiving data" << std::endl;
                break;  // Exit the inner loop on error
            }

            // Check for the end of communication based on your protocol
            if (strcmp(buffer, "END_OF_COMMUNICATION") == 0) {
                break;  // Exit the inner loop if the server signals the end
            }
        }

        command.clear();
    }


    closesocket(clientSocket);
    WSACleanup();
}

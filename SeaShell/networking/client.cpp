#include "client.hpp"
#include <ws2ipdef.h>
#include <ws2tcpip.h>


void ConnectToServer(Arguments args, Options options) {

    const std::string serverIP = args.empty() ? "::1" : args[0];
    const std::string serverPort = (args.size() == 2) ? args[1] : "8080";
    string serverName;
    if (serverIP == "::1") {
        serverName = "localhost";
    } else {
        serverName = serverIP;
    }
}

#include "clientsend.hpp"
#include <iostream>

void SendClient(const CommandArgs& args) {
    if(args.argCount() != 2) {
        std::cerr << "Usage: send <ip> <port>" << std::endl;
        return;
    }

    const std::string& ip = args.getArg(0);
    const std::string& port = args.getArg(1);

    std::cout << "Sending client to " << ip << ":" << port << std::endl;
}
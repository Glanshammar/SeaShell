#include "ip.hpp"

void PrintInterface(const Poco::Net::NetworkInterface& networkInterface) {
    cout << "Interface: " << std::flush;
    cout << networkInterface.name() << std::endl;

    cout << "  Display Name: " << std::flush;
    cout << networkInterface.displayName() << std::endl;

    cout << "  MAC Address: " << std::flush;
    cout << networkInterface.macAddress() << std::endl;

    for (const auto& address : networkInterface.addressList()) {
        const auto& ipAddress = address.get<0>();
        const auto& netmask = address.get<1>();
        const auto& broadcastAddress = address.get<2>();

        cout << "  IP Address: " << std::flush;
        cout << ipAddress.toString() << std::endl;

        cout << "  Netmask: " << std::flush;
        cout << netmask.toString() << std::endl;

        cout << "  Broadcast Address: " << std::flush;
        cout << broadcastAddress.toString() << std::endl;
    }

    cout << std::endl;
}

void ListInterfaces(Arguments args, Options options) {
    try {
        auto interfaces = Poco::Net::NetworkInterface::list();
        for (const auto& networkInterface : interfaces) {
            PrintInterface(networkInterface);
        }
    } catch (Poco::Exception& ex) {
        std::cerr << "Error: " << ex.displayText() << std::endl;
        return;
    }
}
#include "ip.hpp"

void PrintInterface(const Poco::Net::NetworkInterface& networkInterface) {
    setColor(Color::YELLOW);
    cout << "Interface: " << std::flush;
    setColor(Color::WHITE);
    cout << networkInterface.name() << std::endl;

    setColor(Color::CYAN);
    cout << "  Display Name: " << std::flush;
    setColor(Color::WHITE);
    cout << networkInterface.displayName() << std::endl;

    setColor(Color::CYAN);
    cout << "  MAC Address: " << std::flush;
    setColor(Color::WHITE);
    cout << networkInterface.macAddress() << std::endl;

    for (const auto& address : networkInterface.addressList()) {
        const auto& ipAddress = address.get<0>();
        const auto& netmask = address.get<1>();
        const auto& broadcastAddress = address.get<2>();

        setColor(Color::CYAN);
        cout << "  IP Address: " << std::flush;
        setColor(Color::WHITE);
        cout << ipAddress.toString() << std::endl;

        setColor(Color::CYAN);
        cout << "  Netmask: " << std::flush;
        setColor(Color::WHITE);
        cout << netmask.toString() << std::endl;

        setColor(Color::CYAN);
        cout << "  Broadcast Address: " << std::flush;
        setColor(Color::WHITE);
        cout << broadcastAddress.toString() << std::endl;
    }
    setColor(Color::DEFAULT);
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
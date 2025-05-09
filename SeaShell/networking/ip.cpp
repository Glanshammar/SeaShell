#include "../common.hpp"
#include "ip.hpp"

void PrintInterface(const Poco::Net::NetworkInterface& networkInterface) {
    cout << "Interface: " << flush;
    cout << networkInterface.name() << endl;

    cout << "  Display Name: " << flush;
    cout << networkInterface.displayName() << endl;

    cout << "  MAC Address: " << flush;
    cout << networkInterface.macAddress() << endl;

    for (const auto& address : networkInterface.addressList()) {
        const auto& ipAddress = address.get<0>();
        const auto& netmask = address.get<1>();
        const auto& broadcastAddress = address.get<2>();

        cout << "  IP Address: " << flush;
        cout << ipAddress.toString() << endl;

        cout << "  Netmask: " << flush;
        cout << netmask.toString() << endl;

        cout << "  Broadcast Address: " << flush;
        cout << broadcastAddress.toString() << endl;
    }

    cout << endl;
}

void ListInterfaces(Arguments args, Options options) {
    try {
        auto interfaces = Poco::Net::NetworkInterface::list();
        for (const auto& networkInterface : interfaces) {
            PrintInterface(networkInterface);
        }
    } catch (Poco::Exception& ex) {
        cerr << "Error: " << ex.displayText() << endl;
        return;
    }
}
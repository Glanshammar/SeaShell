#include "ssh.hpp"

socket_t CreateSocket(const char* hostname, int port) {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock\n";
        return INVALID_SOCKET;
    }
#endif

    // Create a socket
    socket_t sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1) {
        std::cerr << "Failed to create socket\n";
        return INVALID_SOCKET;
    }

    // Resolve the server address and port
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    if (inet_pton(AF_INET, hostname, &sin.sin_addr) <= 0) {
        std::cerr << "Invalid hostname or IP address\n";
        close(sock);
        return INVALID_SOCKET;
    }

    // Connect to the server
    if (connect(sock, (sockaddr*)&sin, sizeof(sin)) != 0) {
        std::cerr << "Failed to connect to the server\n";
        close(sock);
        return INVALID_SOCKET;
    }

    return sock;
}

void ConnectToSSH(Arguments args, Options options){
    if(args.size() < 3 || args.size() > 3 || options[0] == "-h" || options[0] == "-help"){
        std::cerr << "Usage: ssh <hostname> <username> <password>\n";
        std::cerr << "If no password, use 'none'.\n";
        return;
    }
    const char* hostname = args[0].c_str();
    const char* username = args[1].c_str();
    const char* password = args[2].c_str();
    if(password == "none"){
        password = "";
    }
    int port = 22;

    // Initialize libssh2
    if (libssh2_init(0) != 0) {
        std::cerr << "libssh2 initialization failed\n";
        return;
    }

    // Create an SSH session
    LIBSSH2_SESSION* session = libssh2_session_init();
    if (!session) {
        std::cerr << "Failed to create SSH session\n";
        return;
    }

    // Connect to the SSH server using the cross-platform socket creation function
    socket_t sock = CreateSocket(hostname, port);
    if (sock == INVALID_SOCKET) {
        libssh2_session_free(session);
        libssh2_exit();
        return;
    }

    // Establish the SSH session
    if (libssh2_session_handshake(session, sock)) {
        std::cerr << "Failed to establish SSH session\n";
        libssh2_session_disconnect(session, "Normal Shutdown");
        libssh2_session_free(session);
        libssh2_exit();
        close(sock);
        return;
    }

    // Authenticate with the server
    if (libssh2_userauth_password(session, username, password)) {
        std::cerr << "Authentication by password failed\n";
        libssh2_session_disconnect(session, "Normal Shutdown");
        libssh2_session_free(session);
        libssh2_exit();
        close(sock);
        return;
    }

    std::cout << "SSH authentication succeeded!\n";

    // Clean up and shutdown
    libssh2_session_disconnect(session, "Normal Shutdown");
    libssh2_session_free(session);
    libssh2_exit();
    close(sock);

#ifdef _WIN32
    WSACleanup();
#endif
}
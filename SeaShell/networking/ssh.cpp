#include "ssh.hpp"

void HandleConnection(LIBSSH2_SESSION* session, int sock) {
    // Start an SSH session for the accepted connection
    if (libssh2_session_handshake(session, sock)) {
        std::cerr << "Failed to establish SSH session\n";
        close(sock);
        return;
    }

    // Authenticate the client using a password (for simplicity)
    const char* username = "mondus";  // Replace with actual username
    const char* password = "";  // Replace with actual password

    if (libssh2_userauth_password(session, username, password)) {
        std::cerr << "Authentication failed\n";
        libssh2_session_disconnect(session, "Normal Shutdown");
        libssh2_session_free(session);
        close(sock);
        return;
    }

    std::cout << "Client authenticated successfully\n";

    // Create a channel
    LIBSSH2_CHANNEL* channel = libssh2_channel_open_session(session);
    if (!channel) {
        std::cerr << "Failed to open SSH channel\n";
        libssh2_session_disconnect(session, "Normal Shutdown");
        libssh2_session_free(session);
        close(sock);
        return;
    }

    // Execute a command on the channel
    const char* command = "uptime";  // Replace with actual command
    if (libssh2_channel_exec(channel, command)) {
        std::cerr << "Failed to execute command\n";
        libssh2_channel_close(channel);
        libssh2_channel_free(channel);
        libssh2_session_disconnect(session, "Normal Shutdown");
        libssh2_session_free(session);
        close(sock);
        return;
    }

    // Read the command output
    char buffer[1024];
    int rc;
    while ((rc = libssh2_channel_read(channel, buffer, sizeof(buffer))) > 0) {
        std::cout.write(buffer, rc);
    }

    if (rc < 0) {
        std::cerr << "Failed to read command output\n";
    }

    // Close the channel
    libssh2_channel_close(channel);
    libssh2_channel_free(channel);

    // Disconnect the session and free resources
    libssh2_session_disconnect(session, "Normal Shutdown");
    libssh2_session_free(session);
    close(sock);
}

void StartSSHServer(Arguments args, Options options){
    if(args.empty() && options.empty()){
        std::cerr << "Usage: ssh -s/-start <port>" << std::endl;
        return;
    }

    cout << "Starting SSH server..." << std::endl;


    int port = std::stoi(args[0]);
    if (port < 0 || port > 65535) {
        std::cerr << "Invalid port number" << std::endl;
        return;
    }
    // Initialize libssh2
    if (libssh2_init(0) != 0) {
        std::cerr << "libssh2 initialization failed" << std::endl;
        return;
    }

    // Create an SSH session
    LIBSSH2_SESSION *session = libssh2_session_init();
    if (!session) {
        std::cerr << "Failed to create SSH session" << std::endl;
        return;
    }

    // Create a listener socket
    socket_t listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == INVALID_SOCKET) {
        std::cerr << "Failed to create listener socket" << std::endl;
        libssh2_session_free(session);
        libssh2_exit();
        return;
    }

    // Bind the listener socket to the specified port
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = INADDR_ANY;
    if (bind(listener, (sockaddr *) &sin, sizeof(sin)) != 0) {
        std::cerr << "Failed to bind listener socket" << std::endl;
        close(listener);
        libssh2_session_free(session);
        libssh2_exit();
        return;
    }

    // Listen for incoming connections
    if (listen(listener, 2) != 0) {
        std::cerr << "Failed to listen for incoming connections\n";
        close(listener);
        libssh2_session_free(session);
        libssh2_exit();
        return;
    }

    std::cout << "Listening for incoming SSH connections on port " << port << "...\n";

    while (true) {
        socket_t sock = accept(listener, nullptr, nullptr);
        if (sock == INVALID_SOCKET) {
            std::cerr << "Failed to accept incoming connection\n";
            close(listener);
            libssh2_session_free(session);
            libssh2_exit();
            return;
        }

        std::thread(HandleConnection, session, sock).detach();
    }
}

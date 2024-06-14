#pragma once

#include "../global.hpp"
#include <libssh2.h>
#include <libssh2_sftp.h>
#include <libssh2_publickey.h>
#include <cerrno>



#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#ifdef _WIN32
using socket_t = SOCKET;
#else
using socket_t = int;
#endif

void StartSSHServer(Arguments args, Options options);
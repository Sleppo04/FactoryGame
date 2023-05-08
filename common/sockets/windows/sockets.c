#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include "../sockets.h"

void InitSockets()
{
    WSADATA wsa;
    
    if(WSAStartup(MAKEWORD(2, 0), &wsa)) {
        printf("ERROR: Couldn't initialize WinSock!\n");
    }
}

socket_t CreateSocket(char* address, unsigned short port)
{
    SOCKET sock;
    SOCKADDR_IN* addr;
    long rc;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock == INVALID_SOCKET) {
        printf("ERROR: Couldn't create WinSock-Socket.\n");
        return 0;
    }
    
    addr = (SOCKADDR_IN*) calloc(1, sizeof(SOCKADDR_IN));
    addr->sin_family = AF_INET;
    addr->sin_port   = htons(port);
    addr->sin_addr.s_addr = inet_addr(address);

    rc = connect(sock, (SOCKADDR*) addr, sizeof(SOCKADDR));

    if(rc == SOCKET_ERROR) {
        printf("ERROR: Couldn't open socket to address %s on port %u!\n", address, port);
        return 0;
    }

    return (socket_t) sock;
}

void SendSocket(socket_t socket, char* data, size_t size)
{
    send((SOCKET)socket, data, size, 0);
}

int RecvSocket(socket_t socket, char* buffer, size_t size)
{
    return recv((SOCKET)socket, buffer, size, 0);
}

void CloseSocket(socket_t socket)
{
    closesocket((SOCKET) socket);
}

void CleanupSockets()
{
    WSACleanup();
}
#ifndef SOCKETS_H
#define SOCKETS_H

typedef void* socket_t;

void     InitSockets();

socket_t CreateSocket(char* address, unsigned short port);
void     SendSocket(socket_t socket, char* data, size_t size);
int      RecvSocket(socket_t socket, char* buffer, size_t size);
void     CloseSocket(socket_t socket);

void     CleanupSockets();

#endif // SOCKETS_H
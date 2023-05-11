#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../sockets.h"

// Local functions not in the header file

// This function does not set errno but rather returns an error code
// This function does set errno, but that's not intended
int sockets_close_fd(int fd, int tries)
{
	int close_code;

	for (int i = 0; i < tries; i++) {
		close_code = close(fd);

		if (close_code == 0) {
			// success
			break;
		}

		if (errno == EBADF) {
			// fd is no valid file
			// further trying is of no use
			break;
		}

		// EIO and EINTR can be retried
	}

	return close_code == 0 ? 0 : errno;
}



// Functions from the header file

void InitSockets()
{
	// POSIX doesn't need this afaik, just don't do anything
	return;
}

socket_t CreateSocket(char* address, unsigned short port)
{
	if (address == NULL) {
		errno = EINVAL; // invalid argument
		return NULL;
	}

	int close_code;


	// Create destination address struct
	struct sockaddr_in in_address;
	int aton_code;
	in_address.sin_family = AF_INET;
	in_address.sin_port   = htons(port); // Convert port number to network bytes
	aton_code = inet_aton(address, &(in_address.sin_addr));
	if (aton_code == 0) {
		errno = EINVAL; // bad string
		return NULL;
	}


	// Create socket file descriptor
	int socket_fd;
	// TODO: Maybe use a specific protocol to ensure everyone's using the same
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (socket_fd == -1) {
		// errno is set from socket()
		return NULL;
	}


	// Connect socket to target address
	// connect auto-binds if not already bound
	int connect_code;
	const struct sockaddr* const_in_addr_ref = (struct sockaddr*) &in_address;
	connect_code = connect(socket_fd, const_in_addr_ref, sizeof(struct sockaddr_in));

	// if failure
	if (connect_code == -1) {
		sockets_close_fd(socket_fd, 10); 
		// cleanup file-descriptor, 10 tries
		// if this fails, I have no means of returning this fd to the system
		// TODO: Find solution for uncloseable fd

		// errno is set by connect()
		return NULL;
	}


	// allocate a place for the socket-file-descriptor to match the generic return type
	int* socket_fd_location = malloc(sizeof(int));

	if (socket_fd_location == NULL) {
		sockets_close_fd(socket_fd, 10); 
		// cleanup file-descriptor, 10 tries
		// if this fails, I have no means of returning this fd to the system
		// TODO: Find solution for uncloseable fd
		
		errno = ENOMEM; // set errno appropriately
		return NULL;
	}

	socket_fd_location[0] = socket_fd;

	return (socket_t) (void*) socket_fd_location;
}

void SendSocket(socket_t socket, char* data, size_t size)
{
	int socket_fd  = ((int*) socket)[0];
	void* buffer   = data;
	ssize_t bytes_send;

	bytes_send = send(socket_fd, buffer, size, 0);

	// TODO: User has to detect success themselves?
	// TODO: Maybe allow a return value in the header
	return;
}

int RecvSocket(socket_t socket, char* buffer, size_t length)
{
	int socket_fd  = ((int*) socket)[0];

	return recv(socket_fd, buffer, length, 0);
}

void CloseSocket(socket_t socket)
{
	int socket_fd  = ((int*) socket)[0];

	sockets_close_fd(socket_fd, 10);
	// Close with 10 tries, this function allow no return, so we don't care about it
	
	free(socket); // free the area the socket fd was stored in
	
	return;
}

void CleanupSockets()
{
	// Windows stuff we don't need here I believe
}

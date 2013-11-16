#pragma once

#include <iostream>
#include <stdio.h>
#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define UNINITIALIZED_SOCKET (-2)
#define BAD_PROTOCOL (-3)

enum	proto
{
	NONE,
	TCP,
	UDP
};

class	SocketWindows
{
	SOCKET		_socket;
	SOCKADDR_IN	_sin;
	proto		_type;
	bool		_ifClosed;

public:
	SocketWindows(void);
	virtual ~SocketWindows(void);
	int		getSocket() const;
	struct sockaddr_in *getSockaddr() const;
	bool		isClosed() const;
	void		setSocket(SOCKET &);
	void		setSin(SOCKADDR_IN &);
	void		setIfClosed(bool closed);
	void		setType(proto type);

	bool		winSockInitialized() const;
	bool		loadWinSock() const;

	bool		init(proto type);
	bool		Bind(char *, unsigned int);
	bool		Listen(int queue);
	bool		Connect(char *ip, unsigned int port);
	SocketWindows *Accept();

	bool		Close();
	int			Recv(void *buff, int size);
	int			Send(const void *to_send, int size);
	int			sendTo(void *to_send, int size, struct sockaddr_in *dest);
	int			recvFrom(void *buff, int size, struct sockaddr_in *sender);
};

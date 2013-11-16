#include "SocketWindows.h"


SocketWindows::SocketWindows(void) : _socket(INVALID_SOCKET), _ifClosed(true), _type(NONE) {}

SocketWindows::~SocketWindows(void)
{
	if (!this->_ifClosed)
		closesocket(this->_socket);
}

int		SocketWindows::getSocket() const
{
	return (this->_socket);
}

struct sockaddr_in	*SocketWindows::getSockaddr() const
{
	return (sockaddr_in *)&(this->_sin);
}

bool		SocketWindows::isClosed() const
{
	return this->_ifClosed;
}

void		SocketWindows::setSocket(SOCKET &sock)
{
	this->_socket = sock;
}

void		SocketWindows::setSin(SOCKADDR_IN &sin)
{
	this->_sin = sin;
}

void		SocketWindows::setIfClosed(bool closed)
{
	this->_ifClosed = closed;
}

void		SocketWindows::setType(proto type)
{
	this->_type = type;
}

bool		SocketWindows::winSockInitialized() const
{
	SOCKET s = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, 0);
    if (s == INVALID_SOCKET && WSAGetLastError() == WSANOTINITIALISED)
        return false;
	closesocket(s);
    return true;
}

bool		SocketWindows::loadWinSock() const
{
	WSADATA WSAData;

	std::cout << "Loading Winsock.dll 2.2..." << std::endl;
	if (WSAStartup(MAKEWORD(2, 2), &WSAData))
	{
		std::cerr << "WSAStartup error" << std::endl;
		return false;
	}
	if (LOBYTE(WSAData.wVersion) != 2 || HIBYTE(WSAData.wVersion) != 2)
	{
        std::cerr << "Could not find a usable version of Winsock.dll" << std::endl;
        WSACleanup();
        return false;
    }
	std::cout << "J'ai load le Winsock.dll" << std::endl;
	return true;
}

bool		SocketWindows::init(proto type)
{
	if (!winSockInitialized())
	{
		if (!this->loadWinSock())
			return (false);
	}

	std::cout << "Creating socket..." << std::endl;
	if (type == UDP)
	{
		if ((this->_socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, 0/*WSA_FLAG_OVERLAPPED*/)) == INVALID_SOCKET)
		{
			std::cout << "Error with creating socket" << std::endl;
			return false;
		}
	}
	else if (type == TCP)
	{
		if ((this->_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0/*WSA_FLAG_OVERLAPPED*/)) == INVALID_SOCKET)
		{
			std::cout << "Error with creating socket" << std::endl;
			return false;
		}
	}
	else
		return false;
	this->_type = type;
	std::cout << "Socket created" << std::endl;
	this->_ifClosed = false;
	return true;
}

bool		SocketWindows::Bind(char *ip, unsigned int port)
{
	 if (this->_ifClosed)
		return false;

	if (!ip)
		this->_sin.sin_addr.s_addr = INADDR_ANY;
	else
		this->_sin.sin_addr.s_addr = inet_addr(ip);
	this->_sin.sin_family = AF_INET;
	this->_sin.sin_port = htons(port);
	if (bind(this->_socket, (SOCKADDR *)&this->_sin, sizeof(this->_sin)))
		return false;

	return true;
}

bool		SocketWindows::Listen(int queue)
{
	if (this->_ifClosed == true || this->_type != TCP)
		return false;
	if (listen(this->_socket, queue))
		return false;
	return true;
}

bool		SocketWindows::Connect(char *ip, unsigned int port)
{
	struct sockaddr_in	sin;
	
	if (this->_ifClosed == true || this->_type != TCP)
		return false;

	sin.sin_addr.s_addr	= inet_addr(ip);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);

	if (WSAConnect(this->_socket, reinterpret_cast<SOCKADDR *>(&sin), sizeof(sin), NULL, NULL, NULL, NULL))
		return false;
	return true;
}



bool		SocketWindows::Close()
{
  if (this->_ifClosed)
    return false;
  closesocket(this->_socket);
  this->_ifClosed = true;
  this->_type = NONE;
  return true;
}

SocketWindows	*SocketWindows::Accept()
{
	SocketWindows *client;
	SOCKET client_sock;
	sockaddr_in clientsin;
	int clientsin_size = sizeof(clientsin);

	if (this->_ifClosed || this->_type != TCP)
		return NULL;

	if ((client_sock = WSAAccept(this->_socket, reinterpret_cast<SOCKADDR *>(&clientsin), &clientsin_size, NULL, NULL)) == INVALID_SOCKET)
		return NULL;
	client = new SocketWindows();
	client->setSocket(client_sock);
	client->setSin(clientsin);
	client->setIfClosed(false);
	client->setType(TCP);
	return client;
}

int		SocketWindows::Recv(void *buffer, int size)
{
	WSABUF buff;
	int	size_sin = sizeof(struct sockaddr_in);
	unsigned long int readed = 0;
	unsigned long int flagrecv = 0;

	if (this->_ifClosed)
		return UNINITIALIZED_SOCKET;
	if (this->_type != TCP)
		return BAD_PROTOCOL;

	buff.len = size;
	buff.buf = reinterpret_cast<char *>(buffer);

	if (WSARecv(this->_socket, &buff, 1, &readed, &flagrecv, NULL, NULL))
		return (-1);
	return readed;
}

int			SocketWindows::Send(const void *to_send, int size)
{
	WSABUF buff;
	unsigned long int		lpNumberOfBitSent;

	buff.len = size;
	buff.buf = reinterpret_cast<char *>(const_cast<void *>(to_send));

	if (WSASend(this->_socket, &buff, 1, &lpNumberOfBitSent, NULL, NULL, NULL))
		return (-1);
	return lpNumberOfBitSent;
}


int	SocketWindows::sendTo(void *to_send, int size, struct sockaddr_in *dest)
{
	WSABUF buff;
	unsigned long int		lpNumberOfBitSent;

	if (this->_ifClosed)
		return UNINITIALIZED_SOCKET;

	buff.len = size;
	buff.buf = reinterpret_cast<char *>(to_send);
	if (WSASendTo(this->_socket, &buff, 1, &lpNumberOfBitSent, NULL, (SOCKADDR *)dest, sizeof(*dest), NULL, NULL) != 0)
		return (-1);
	return lpNumberOfBitSent;
}

int	SocketWindows::recvFrom(void *buff, int size, struct sockaddr_in *sender)
{
	WSABUF	tmp;
	int	size_sin = sizeof(*sender);
	unsigned long int readed = 0;
	unsigned long int flagrecv = 0;

	if (this->_ifClosed)
		return UNINITIALIZED_SOCKET;
	tmp.len = size;
	tmp.buf = reinterpret_cast<char *>(buff);
	if (WSARecvFrom(this->_socket, &tmp, 1, &readed, &flagrecv, (SOCKADDR *)sender, &size_sin, NULL, NULL) != 0 || readed == 0)
		return (-1);
	return readed;
}

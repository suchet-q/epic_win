#pragma once

#ifdef	_WIN32
# include "SocketWindows.h"
#else
# include "Linux/SocketLinux.h"
#endif

template<class T =
#ifdef _WIN32
	SocketWindows
#else
	SocketLinux
#endif
>
class MetaSocket
{

	T			_socket;

public:
	MetaSocket(void){}
	MetaSocket(const T &copy)
	{
		this->_socket = copy;
	}

	~MetaSocket(void){}

	int					getSocket() const
	{
		return (this->_socket.getSocket());
	}
	
	struct sockaddr_in	*getSockaddr() const
	{
		return (this->_socket.getSockaddr());
	}

	bool		init(proto type) // best jeu de mots EU
	{
		return (this->_socket.init(type));
	}

	bool		Bind(char *ip, unsigned int port)
	{
		return this->_socket.Bind(ip, port);
	}

	bool		Listen(int queue)
	{
		return this->_socket.Listen(queue);
	}

	bool		Connect(char *ip, unsigned int port)
	{
		return this->_socket.Connect(ip, port);
	}

	MetaSocket<T>	*Accept()
	{
		T *new_client = this->_socket.Accept();
		
		if (new_client)
			return new MetaSocket<T>(*new_client);
		return NULL;
	}

	bool		Close()
	{
		return (this->_socket.Close());
	}

	int		Recv(void *buff, int size)
	{
		return this->_socket.Recv(buff, size);
	}

	int		Send(const void *to_send, int size)
	{
		return this->_socket.Send(to_send, size);
	}

	int sendTo(void *to_send, int size, struct sockaddr_in *dest)
	{
		return (this->_socket.sendTo(to_send, size, dest));
	}
	int recvFrom(void *buff, int size, struct sockaddr_in *sender)
	{
		return (this->_socket.recvFrom(buff, size, sender));
	}
	struct sockaddr_in*	getServerSockaddr(char *ip, unsigned int port)
	{
        struct addrinfo hints, *res;
	std::stringstream		ss;
	
	ss << port;
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_INET;                                                                                                                                               
        hints.ai_socktype = SOCK_DGRAM;                                                                                                                                                                         
        getaddrinfo(ip, ss.str().c_str(), &hints, &res);
        return (res->ai_addr);
	}
};

#include "GameSocket.h"

GameSocket::GameSocket(void)
{
	this->_tcpRunning = false;
	this->_udpRunning = false;
	this->_sin = NULL;
}

GameSocket::~GameSocket(void)
{
}

void			GameSocket::setValues(std::string const &ip, int port)
{
	this->_ip = ip;
	this->_port = port;
}

void			GameSocket::setUDPPort(int port)
{
	this->_udpPort = port;
}

bool			GameSocket::connectTCP()
{
	if (!(this->_tcpRunning))
	{
		this->_socket.init(TCP);
		if (this->_socket.Connect(const_cast<char *>(this->_ip.c_str()), this->_port))
			this->_tcpRunning = true;
	}
	return (this->_tcpRunning);
}

bool			GameSocket::connectUDP()
{
	if (!(this->_udpRunning))
	{
		this->_socketUDP.init(UDP);
		std::cout << "UDP Port : " << this->_udpPort << std::endl;
		if (this->_socketUDP.Bind(const_cast<char *>(this->_ip.c_str()), 0))
		{
			this->_udpRunning = true;
			this->_sin = this->_socketUDP.getServerSockaddr(const_cast<char *>(this->_ip.c_str()), this->_udpPort);
		}
	}
	return (this->_udpRunning);
}

void			GameSocket::disconnectUDP()
{
	if (this->_udpRunning)
	{
		this->_socketUDP.Close();
		this->_udpRunning = false;
	}
}

void			GameSocket::disconnectTCP()
{
	if (this->_tcpRunning)
	{
		this->_socket.Close();
		this->_tcpRunning = false;
	}
}
void			GameSocket::update(Parser &parser)
{
	fd_set		readFd;
	fd_set		writeFd;
	std::pair<void *, int>	cmd;
	std::pair<void *, int>	cmdUDP;
	char		rec[512];

	this->_select.fdZero(&readFd);
	this->_select.fdZero(&writeFd);
	this->_select.fdSet(this->_socket, &readFd);
	if (this->_udpRunning)
		this->_select.fdSet(this->_socketUDP, &readFd);

	cmd = parser.getQueued();
	cmdUDP = parser.getQueuedUDP();
	if (cmd.first != NULL)
		this->_select.fdSet(this->_socket, &writeFd);
	if (!(this->_select.Select(&readFd, &writeFd, 1000)))
		throw RuntimeException("[GameSocket::update]", "Select failed on socket");
	if (this->_select.fdIsset(this->_socket, &readFd))
	{
		memset(rec, 0, 512);
		parser.parse(&rec, this->_socket.Recv(rec, 512));
	}
	if (cmd.first != NULL && this->_select.fdIsset(this->_socket, &writeFd))
		this->_socket.Send(cmd.first, cmd.second);
	if (this->_udpRunning && this->_select.fdIsset(this->_socketUDP, &readFd))
	{
		memset(rec, 0, 512);
		parser.parse(&rec, this->_socketUDP.recvFrom(rec, 512, this->_sin));
		parser.setStartUDP();
	}
	while (this->_udpRunning && cmdUDP.first != NULL)
	{
		this->_socketUDP.sendTo(cmdUDP.first, cmdUDP.second, this->_sin);
		cmdUDP = parser.getQueuedUDP();
	}
}

#include "GameSocket.h"

GameSocket::GameSocket(void)
{
	this->_tcpRunning = false;
}

GameSocket::~GameSocket(void)
{
}

void			GameSocket::setValues(std::string const &ip, int port)
{
	this->_ip = ip;
	this->_port = port;
}

void			GameSocket::connectTCP()
{
	if (!(this->_tcpRunning))
	{
		this->_socket.init(TCP);
		if (this->_socket.Connect(const_cast<char *>(this->_ip.c_str()), this->_port))
			this->_tcpRunning = true;
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
	char		rec[512];

	this->_select.fdZero(&readFd);
	this->_select.fdZero(&writeFd);
	this->_select.fdSet(this->_socket, &readFd);
	cmd = parser.getQueued();
	if (cmd.first != NULL)
		this->_select.fdSet(this->_socket, &writeFd);
	if (!(this->_select.Select(&readFd, &writeFd, 1000)))
		std::cout << "SELECT FAIL IMPOSSIBLU" << std::endl;
	if (this->_select.fdIsset(this->_socket, &readFd))
	{
		memset(rec, 0, 512);
		parser.parse(&rec, this->_socket.Recv(rec, 512));
	}
	if (cmd.first != NULL && this->_select.fdIsset(this->_socket, &writeFd))
		this->_socket.Send(cmd.first, cmd.second);
}
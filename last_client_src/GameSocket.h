#pragma once

#include	<list>
#include	<map>
#include	"Macros.h"
#include	"MetaSocket.h"
#include	"MetaSelect.h"
#include	"Parser.h"
#include	"RuntimeException.h"

class GameSocket
{
	MetaSocket<>			_socket;
	MetaSocket<>			_socketUDP;
	MetaSelect<>			_select;
	std::string				_ip;
	int						_port;
	int						_udpPort;
	bool					_tcpRunning;
	bool					_udpRunning;
	struct sockaddr_in*		_sin;
public:
	GameSocket(void);
	~GameSocket(void);

	void			update(Parser &);
	void			setValues(std::string const &, int);
	void			setUDPPort(int);
	bool			connectTCP();
	void			disconnectTCP();
	bool			connectUDP();
	void			disconnectUDP();
};


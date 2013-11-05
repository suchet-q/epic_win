#pragma once

#include	<list>
#include	<map>
#include	"Macros.h"
#include	"MetaSocket.h"
#include	"MetaSelect.h"
#include	"Parser.h"

class GameSocket
{
	MetaSocket<>			_socket;
	MetaSelect<>			_select;
	std::string				_ip;
	int						_port;
	int						_udpPort;
	bool					_tcpRunning;
	bool					_udpRunning;
public:
	GameSocket(void);
	~GameSocket(void);

	void			update(Parser &);
	void			setValues(std::string const &, int, int);
	bool			connectTCP();
	void			disconnectTCP();
	bool			connectUDP();
	void			disconnectUDP();
};


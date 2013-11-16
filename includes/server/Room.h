#pragma once
#include	<iostream>
#include	<string>
#include	<list>
#include	"Client.h"

class Room
{
private:
	int		_id;
	std::list<Client *> _clients;
	Client	*_host;
public:
	Room(int, Client *);
	Room();
	~Room();
	void		sendMsg(void *command);
	void		setID(int);
	int			getID() const;
	void		setHost(Client const *);
	Client	const *getHost() const;
	bool		addClient(Client *);
	Client		*delClient(int);
	std::list<Client *>	*getClient() const;
};


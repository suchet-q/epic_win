#pragma once
#include	<list>
#include	<iostream>
#include	<string>
#include	"Client.h"

struct t_udpcmd
{
	unsigned char cmd[4];
	unsigned char size;
	struct sockaddr_in	sockaddrclient;
};

class ResourcesGame
{
private:
	std::list<Client *>	*_clients;
	std::list<t_udpcmd>	_readBuffer;
public:
	ResourcesGame(std::list<Client *> *);
	ResourcesGame();
	~ResourcesGame();
	std::list<Client *>		&getClients();
	void		setListClients(std::list<Client *> *);
	std::list<t_udpcmd>	&getUDPCmd();
};


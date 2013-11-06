#pragma once
#include	<list>
#include	<iostream>
#include	<string>
#include	"Client.h"

class ResourcesGame
{
private:
	std::list<Client *>	*_clients;
public:
	ResourcesGame(std::list<Client *> *);
	ResourcesGame();
	~ResourcesGame();
	std::list<Client *>		&getClients();
	void		setListClients(std::list<Client *> *);
};


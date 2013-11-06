#include "ResourcesGame.h"


ResourcesGame::ResourcesGame(std::list<Client *> *clients)
{
	this->_clients = clients;
}

ResourcesGame::ResourcesGame() {}

ResourcesGame::~ResourcesGame() {}

std::list<Client *>		&ResourcesGame::getClients()
{
	return (*this->_clients);
}

void		ResourcesGame::setListClients(std::list<Client *> *clients)
{
	this->_clients = clients;
}
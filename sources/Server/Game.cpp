#include "Game.h"


Game::Game(int id, std::list<Client *> *clients)
{
	this->_id = id;
	//this->_resources->setListClients(clients);
}

Game::Game() {}

Game::~Game() {}

int		Game::startGame(void* st)
{

	/*identification verifier nchanger status dans infos client puis lancer la game*/
	/*appel de methode init etc... et la loop de la game*/
	return (true);
}

void	Game::setID(int id)
{
	this->_id = id;
}

int		Game::getID()
{
	return (this->_id);
}

void	Game::setResources(ResourcesGame *resources)
{
	this->_resources = resources;
}

ResourcesGame	&Game::getResources()
{
	return (*this->_resources);
}

void		Game::setThread(MetaThreader<Game, void> *thread)
{
	this->_thread = thread;
}

#include "Game.h"


Game::Game(int id, std::list<Client *> *clients)
{
	this->_id = id;
	this->_resources->setListClients(clients);
}

Game::Game() {}

Game::~Game() {}

void		Game::waitClient()
{
	bool	ok;
	int		nbClient;
	int		available;

	ok = false;
	while (!ok)
	{
		available = 0;
		nbClient = this->_resources->getClients().size();
		for (std::list<t_udpcmd>::iterator itudp = this->_resources->getUDPCmd().begin();
				itudp != this->_resources->getUDPCmd().end(); ++itudp)
		{
			if ((*itudp).size == 4)
			{
				for (std::list<Client *>::iterator it = this->_resources->getClients().begin();
						it != this->_resources->getClients().end(); ++it)
					if ((*it)->getID() == (*itudp).cmd[1])
					{
						(*it)->getInfosClient()->addrClient = (*itudp).sockaddrclient;
						(*it)->getInfosClient()->status = READY;
						++available;
					}
			}
		}
		if (available == nbClient)
			ok = true;
	}
}

bool		Game::startGame()
{
	this->waitClient();
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
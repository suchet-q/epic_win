#include "Resource.h"


Resource::Resource()
{
  for (int i = 0; i < 255; ++i)
    this->_idRooms[i] = false;
  for (int i = 0; i < 255; ++i)
    this->_idGames[i] = false;
}


Resource::~Resource() {}

std::list<Client *>	&Resource::getClients()
{
	return (this->_clients);
}

bool				Resource::checkIfGameIsPossible()
{
	for (int id = 1; id < 255; ++id)
		if (!this->_idGames[id])
			return true;
	return false;
}

std::list<Game *>::iterator &Resource::deleteGame(std::list<Game *>::iterator &it)
{
	this->_idGames[(*it)->getID()] = false;
	it = this->_games.erase(it);
	return (it);
}

bool		Resource::createRoom(Client *client)
{
  for (int id = 1; id < 255; ++id)
    if (!this->_idRooms[id])
      {
		this->_rooms.push_back(new Room(id, client));
		this->_idRooms[id] = true;
		return true;
      }
  return false;
}

std::list<Room *>::iterator &Resource::deleteRoom(std::list<Room *>::iterator &it)
{
	this->_idRooms[(*it)->getID()] = false;
	it = this->_rooms.erase(it);
	return (it);
}

std::list<Room *>		&Resource::getRooms()
{
  return (this->_rooms);
}

bool		Resource::createGame(std::list<Client *> *clients)
{
	for (int id = 1; id < 255; ++id)
		if (!this->_idGames[id])
		{
			this->_games.push_back(new Game(id, clients));
			this->_idGames[id] = true;
			return (true);
		}
	/*create thread*/
	return (false);
}

std::list<Client *> *Resource::getInGameClients()
{
	return (&this->_inGame);
}

std::list<Client *> *Resource::getNotInGameClients()
{
	return (&this->_notInGame);
}

std::list<Game *>	&Resource::getGame()
{
	return (this->_games);
}


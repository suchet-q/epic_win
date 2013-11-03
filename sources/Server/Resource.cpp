#include "Resource.h"


Resource::Resource()
{
	for (int i = 0; i < 255; ++i)
		this->_idRooms[i] = false; 
}


Resource::~Resource() {}

void		Resource::addClient(int id, MetaSocket<> *socket)
{
	this->_clients.push_back(new Client(id, socket));
}

std::list<Client *>	&Resource::getClients()
{
	return (this->_clients);
}

bool		Resource::createRoom(Client *client)
{
	int		id = -1;

	for (int i = 0; i < 255 && id != -1; ++i)
		if (!this->_idRooms[i])
		{
			id = i;
			this->_idRooms[i] = true;
		}
	if (id != -1)
	{
		this->_rooms.push_back(new Room(client->getID(), client));
		return (true);
	}
	return (false);
}

std::list<Room *>		&Resource::getRooms()
{
	return (this->_rooms);
}

void		Resource::createGame(int idClient)
{
	int		find = false;

	for (std::list<Room *>::iterator it = this->_rooms.begin();
			it != this->_rooms.end() && find == false; ++it)
		if ((*it)->getHost()->getID() == idClient)
			{
				it = this->_rooms.erase(it);
				find = true;
			}
	/*cretae thread + rajoute dans la list des game*/
}

/*std::list<Game *> const &Resource::getGame()
{
	return (this->_games);
}*/


#include "Resource.h"


Resource::Resource()
{
  for (int i = 0; i < 255; ++i)
    this->_idRooms[i] = false; 
}


Resource::~Resource() {}

std::list<Client *>	&Resource::getClients()
{
	return (this->_clients);
}

bool		Resource::createRoom(Client *client)
{
  for (int id = 1; id < 255 && !this->_idRooms[id]; ++id)
    if (!this->_idRooms[id])
	{
      this->_rooms.push_back(new Room(id, client));
      this->_idRooms[id] = true;
      return true;
    }
  return false;
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


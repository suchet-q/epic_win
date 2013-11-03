#include "Room.h"


Room::Room(int id, Client *client)
{
  this->_id = id;
  this->_host = client;
}

Room::Room()
{
}

Room::~Room()
{
}

void		Room::sendMsg(void *command)
{
	for (std::list<Client *>::iterator it = this->_clients.begin();
			it != this->_clients.end(); ++it)
		(*it)->addMsgSend(command, sizeof(command));
}

void		Room::setID(int id)
{
	this->_id = id;
}

int			Room::getID() const
{
	return (this->_id);
}

void		Room::setHost(Client const *client)
{
	this->_host = const_cast<Client *>(client);
}

Client	const *Room::getHost() const
{
	return (const_cast<Client *>(this->_host));
}

bool		Room::addClient(Client *client)
{
	if (this->_clients.size() < 4)
	{
		this->_clients.push_back(client);
		return (true);		
	}
	return (false);
}

Client		*Room::delClient(int id)
{
	for (std::list<Client *>::iterator it = this->_clients.begin();
			it != this->_clients.end(); ++it)
		if ((*it)->getID() == id)
		{
			it = this->_clients.erase(it);
			return ((*it));
		}
	return (NULL);
}

std::list<Client *>	*Room::getClient() const
{
	return (const_cast<std::list<Client *> *>(&this->_clients));
}

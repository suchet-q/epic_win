#include		"Server.h"

Server::Server() {}

Server::~Server() {}

bool			Server::init(int port)
{
  if (!this->_network.initSocket(port))
    return false;
  this->_executer.setResource(&this->_resources);
  return true;
}

void			Server::checkDecoClient(std::list<Client *> &to_deco)
{
	t_lvl_client	lvl;
	bool			isInLobby;
	t_cmd			cmd;

	lvl.id_command = 9;
	for (std::list<Client *>::iterator it = to_deco.begin(); it != to_deco.end(); ++it)
	{
		isInLobby = false;
		for (std::list<Room *>::iterator it_room = this->_resources.getRooms().begin(); !isInLobby && it_room != this->_resources.getRooms().end(); ++it_room)
			for (std::list<Client *>::iterator it_client = (*it_room)->getClient()->begin(); !isInLobby && it_client != (*it_room)->getClient()->end(); ++it_client)
				if((*it) == (*it_client))
				{
					isInLobby = true;
					lvl.id_lobby = (*it_room)->getID();
				}
		if (isInLobby)
		{
			lvl.id_client = (*it)->getID();
			memcpy(cmd.cmd, &lvl, sizeof(lvl));
			cmd.size = sizeof(lvl);
			(*it)->getWriteBuffer()->clear();
			this->_executer.execLVL((*it), cmd);
			(*it)->setStatus(TO_LEAVE);
		}
		else
			(*it)->setStatus(TO_DECO);
/*		std::cout << "deleting client " << (*it)->getID() << std::endl;
		delete (*it)->getSocket();
		delete *it;
		it = clientList.erase(it);
		std::cout << "client deleted" << std::endl;*/
	}
}

bool			Server::loop()
{
	bool			error = false;
	std::list<Client *>	buff;
	bool			end_for;

	while (!error)
	{
		this->_network.initSelect(this->_resources.getClients());
		if (this->_network.Select(500))
			this->_network.manageSocket(this->_resources.getClients(), buff);
		else
			error = true;
		end_for = false;
		this->checkDecoClient(buff);
		for (std::list<Client *>::iterator it = this->_resources.getClients().begin();
				!end_for && it != this->_resources.getClients().end(); ++it)
		{
			if ((*it)->getStatus() == TO_DECO)
			{
				std::cout << "deleting client " << (*it)->getID() << std::endl;
				delete (*it)->getSocket();
				delete *it;
				it = this->_resources.getClients().erase(it);
				std::cout << "client deleted" << std::endl;
				if (it == this->_resources.getClients().end())
					end_for = true;
			}
			else if (!(*it)->getReadBuffer()->empty())
			{
				std::cout << "je vais excuter la commande toi meme tu sais" << std::endl;
				if (!this->_executer.executCommand((*it), (*it)->getReadBuffer()->front()))
					error = true;
				(*it)->getReadBuffer()->pop_front();
			}
		}
	}
	return true;
}

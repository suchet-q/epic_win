#include		"Server.h"

Server::Server() {}

Server::~Server() {}

bool			Server::init(int port)
{
  if (!this->_network.initSocket(port))
    return false;
  this->_executer.setResource(&this->_resources);
  for (int i = 0; i < 255; ++i)
	_idArray[i] = false; 
  return true;
}

void			Server::addClient(MetaSocket<> *sockClient)
{
	Client		*newClient;
	t_pnb_server	res;
	t_cmd			cmd;
	bool			accepted = false;

	if (sockClient == NULL)
	{
		std::cout << "Error Accept()" << std::endl;
	    return ;
	}
	for (int id = 0; id < 255 && !accepted; ++id)
		if (!_idArray[id]) {
			std::cout << "adding client " <<  id << std::endl;
			res.id_client = id;
			res.id_command = 0;
			memcpy(cmd.cmd, &res, sizeof(res));
			cmd.size = sizeof(res);
			newClient = new Client(id, sockClient);
			newClient->getWriteBuffer()->push_back(cmd);
			newClient->setStatus(CONNECTED);
			this->_resources.getClients().push_back(newClient);
			this->_resources.getNotInGameClients().push_back(newClient);
			_idArray[id] = true;
		    accepted = true;
			std::cout << "client " << id << " added" << std::endl;
		}
	if (!accepted)
		std::cout << "No more slot available for new client" << std::endl;
}

void			Server::decoNotInGameClient(std::list<Client *>::iterator &it)
{
/*	for (std::list<Client *>::iterator it2 = this->_resources.getClients().begin(); it2 != this->_resources.getClients().end(); ++it2)
		if (*it2 == *it)
		{
			it2 = this->_resources.getClients().erase(it2);
			if (it2 == this->_resources.getClients().end())
				break;
		}*/
	std::cout << "deleting client " << (*it)->getID() << std::endl;
	if ((*it)->getGame())
	{
	// delete game
		//+ prevenir les autres player de la deco de ce pd du cul qui a une connection en bois ou qui rage quit

		for (std::list<Client *>::iterator it2 = this->_resources.getInGameClients().begin(); it2 != this->_resources.getInGameClients().end(); ++it2)
		{
			it2 = this->_resources.getInGameClients().erase(it2);
			if (it2 == this->_resources.getInGameClients().end())
				break;
		}
	}
	else
	{
		for (std::list<Client *>::iterator it2 = this->_resources.getNotInGameClients().begin(); it2 != this->_resources.getNotInGameClients().end(); ++it2)
		{
			it2 = this->_resources.getNotInGameClients().erase(it2);
			if (it2 == this->_resources.getNotInGameClients().end())
				break;
		}
	}
	delete (*it)->getSocket();
	delete *it;
	it = this->_resources.getClients().erase(it);
	std::cout << "client deleted" << std::endl;
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
			this->_executer.execLVL((*it), cmd);
			(*it)->getWriteBuffer()->clear();
			(*it)->setStatus(TO_DECO);
		}
		else
			(*it)->setStatus(TO_DECO);
		_idArray[(*it)->getID()] = false;
	}
	to_deco.clear();
}

bool			Server::loop()
{
	bool			error = false;
	std::list<Client *>	to_deco;
	MetaSocket<>	*added;

	while (!error)
	{
		added = NULL;
		this->_network.initSelect(this->_resources.getClients(), this->_resources.getGame());
		if (this->_network.Select(500))
		{
			this->_network.manageSocket(this->_resources.getClients(), this->_resources.getGame(), to_deco, &added);
		}
		else
		{
			std::cout << "eh oui maggle, le select capu" << std::endl;
			error = true;
		}
		if (added != NULL)
			this->addClient(added);
		if (!to_deco.empty())
		{
			this->checkDecoClient(to_deco);
		}
		for (std::list<Client *>::iterator it = this->_resources.getClients().begin(); it != this->_resources.getClients().end(); ++it)
		{
			if ((*it)->getStatus() == TO_DECO)
			{
				this->decoNotInGameClient(it);
				if (it == this->_resources.getClients().end())
					break;
			}
			else if (!(*it)->getReadBuffer()->empty())
			{
				std::cout << "je vais excuter la commande toi meme tu sais" << std::endl;
				if (!this->_executer.executCommand((*it), (*it)->getReadBuffer()->front()))
					error = true;
				if (it == this->_resources.getClients().end())
					break;
				(*it)->getReadBuffer()->pop_front();
			}
		}

	}
	system("pause");
	return true;
}

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

bool			Server::loop()
{
	bool			error = false;

	while (!error)
	{
		this->_network.initSelect(this->_resources.getClients());
		if (this->_network.Select(500))
			this->_network.manageSocket(this->_resources.getClients());
		else
			error = true;
		for (std::list<Client *>::iterator it = this->_resources.getClients().begin();
				it != this->_resources.getClients().end(); ++it)
		{
			if (!(*it)->getReadBuffer()->empty())
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

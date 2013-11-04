# include		"Network.h"

Network::Network()
{
  for (int i = 0; i < 255; ++i)
    _idArray[i] = false; 

  _commandsSize[1] = 1;
  _commandsSize[2] = 1;
  _commandsSize[3] = 3;
  _commandsSize[4] = 2;
  _commandsSize[6] = 2;
  _commandsSize[7] = 259;
  _commandsSize[8] = 18;
  _commandsSize[9] = 3;
}

Network::~Network() {}

bool			Network::initSocket(int port)
{
  if (!_socket.init(TCP)
      || !_socket.Bind("127.0.0.1", port)
      || !_socket.Listen(42))
    return false;
  return true;
}

void			Network::addClient(MetaSocket<> *socket,
					   std::list<Client *> &clientList)
{

	bool			accepted = false;
	t_pnb_server	res;
	t_cmd			cmd;

  std::cout << "adding client"<< std::endl;
  if (socket == NULL)
    return ;
  for (int id = 0; id < 255 && !accepted; ++id)
    if (!_idArray[id]) {
		res.id_client = id;
		res.id_command = 0;
		memcpy(cmd.cmd, &res, sizeof(res));
		cmd.size = sizeof(res);
		clientList.push_back(new Client(id, socket));
		clientList.back()->getWriteBuffer()->push_back(cmd);
		_idArray[id] = true;
      accepted = true;
    }
  std::cout << "client " << clientList.back()->getID() << " added" << std::endl;
}

void			Network::decoClient(std::list<Client *> &clientList,
					    std::list<Client *>::iterator &it)
{
  _idArray[(*it)->getID()] = false;
  std::cout << "deleting client " << (*it)->getID() << std::endl;
  delete (*it)->getSocket();
  delete *it;
  it = clientList.erase(it);
  std::cout << "client deleted" << std::endl;
}

void			Network::initSelect(std::list<Client *> const &clientList)
{
  _select.fdZero(&_fdWrite);
  _select.fdZero(&_fdRead);
  _select.fdSet(_socket, &_fdRead);
  for (std::list<Client *>::const_iterator it = clientList.begin();
       it != clientList.end(); ++it) {
    _select.fdSet(*(*it)->getSocket(), &_fdRead);
    if (!(*it)->getWriteBuffer()->empty())
      _select.fdSet(*(*it)->getSocket(), &_fdWrite);
  }

}

bool			Network::Select(unsigned int timeval)
{
  if (!_select.Select(&_fdRead, &_fdWrite, timeval))
    return false;
  return true;
}

bool			Network::manageSocket(std::list<Client *> &clientList)
{
  if (_select.fdIsset(_socket, &_fdRead))
    addClient(_socket.Accept(), clientList);

  for (std::list<Client *>::iterator it = clientList.begin();
       it != clientList.end(); ++it) {

    if (!(*it)->getWriteBuffer()->empty()
	&& _select.fdIsset(*(*it)->getSocket(), &_fdWrite))
      sendCommandTCP(*it);

    if (_select.fdIsset(*(*it)->getSocket(), &_fdRead)
	&& recvCommandTCP(*it))
	{
		decoClient(clientList, it);
		if (it == clientList.end())
			break;
	}
  }
  return (true);
}

bool			Network::recvCommandTCP(Client *client)
{
  char			tmp[512];
  int			width = 0;

  if ((width = client->getSocket()->Recv(reinterpret_cast<void *>(tmp), 512)) <= 0)
    return (-1);
  std::cout << "width = " << width << std::endl;
  client->parseCommand(reinterpret_cast<void *>(tmp), static_cast<unsigned int>(width), _commandsSize);
  return (0);
}

bool			Network::sendCommandTCP(Client *client)
{
	std::cout << "Sending command" << std::endl;
  std::cout << client->getWriteBuffer()->size() << std::endl;

	if (client->getSocket()->Send(client->getWriteBuffer()->front().cmd,
				client->getWriteBuffer()->front().size) <= 0)
    return false;
  client->getWriteBuffer()->pop_front();
  return true;
}



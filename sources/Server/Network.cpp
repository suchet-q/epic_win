# include		"Network.h"

Network::Network()
{
  _commandsSize[1] = 1;
  _commandsSize[2] = 1;
  _commandsSize[3] = 3;
  _commandsSize[4] = 2;
  _commandsSize[6] = 2;
  _commandsSize[7] = 259;
  _commandsSize[8] = 18;
  _commandsSize[9] = 3;
  _commandsSize[10] = 8;
  _commandsSize[11] = 3;
  _commandsSize[12] = 2;
  _commandsSize[13] = 2;
  _commandsSize[14] = 4;
  _commandsSize[15] = 2;
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

bool			Network::manageSocket(std::list<Client *> &clientList, std::list<Client *> &to_disconnect, MetaSocket<> **added)
{
  if (_select.fdIsset(_socket, &_fdRead))
    *added = _socket.Accept();

  for (std::list<Client *>::iterator it = clientList.begin();
       it != clientList.end(); ++it) {

    if (!(*it)->getWriteBuffer()->empty()
	&& _select.fdIsset(*(*it)->getSocket(), &_fdWrite))
      sendCommandTCP(*it);

    if (_select.fdIsset(*(*it)->getSocket(), &_fdRead)
	&& !recvCommandTCP(*it))
		to_disconnect.push_back(*it);
  }
  return (true);
}

bool			Network::recvCommandTCP(Client *client)
{
  char			tmp[512];
  int			width = 0;

  if ((width = client->getSocket()->Recv(reinterpret_cast<void *>(tmp), 512)) <= 0)
    return (false);
  std::cout << "width = " << width << std::endl;
  client->parseCommand(reinterpret_cast<void *>(tmp), static_cast<unsigned int>(width), _commandsSize);
  return (true);
}

bool			Network::sendCommandTCP(Client *client)
{
	std::cout << "Sending command" << std::endl;
  std::cout << client->getWriteBuffer()->size() << std::endl;
  if (client->getStatus() == TO_LEAVE)
		client->setStatus(TO_DECO);
  if (client->getSocket()->Send(client->getWriteBuffer()->front().cmd,
				client->getWriteBuffer()->front().size) <= 0)
    return false;
  client->getWriteBuffer()->pop_front();
  return true;
}



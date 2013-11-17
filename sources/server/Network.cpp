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
  _buffer.size = 0;
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

void			Network::initSelect(std::list<Client *> const &clientList, std::list<Game *> &gameList)
{
  _select.fdZero(&_fdWrite);
  _select.fdZero(&_fdRead);
  _select.fdSet(_socket, &_fdRead);

  for (std::list<Client *>::const_iterator it = clientList.begin();
       it != clientList.end(); ++it)
  {
	  if ((*it)->getGame())
			(**((*it)->getGame()))->lockClient();
	 _select.fdSet(*(*it)->getSocket(), &_fdRead);
    if (!(*it)->getWriteBuffer()->empty())
      _select.fdSet(*(*it)->getSocket(), &_fdWrite);
	  if ((*it)->getGame())
		(**((*it)->getGame()))->unlockClient();
  }

  for (std::list<Game *>::iterator it = gameList.begin(); it != gameList.end(); ++it)
  {
	  if ((*it)->getIsInit())
	  {
		 (*it)->lockSocket();
	     _select.fdSet((*it)->getSocket(), &_fdRead);
		 (*it)->unlockAttribut();
	  }
  }
}

bool			Network::Select(unsigned int timeval)
{
  if (!_select.Select(&_fdRead, &_fdWrite, timeval))
    return false;
  return true;
}

bool			Network::manageSocket(std::list<Client *> &clientList, std::list<Game *> &gameList, std::list<Client *> &to_disconnect, MetaSocket<> **added)
{
  if (_select.fdIsset(_socket, &_fdRead))
    *added = _socket.Accept();

  for (std::list<Client *>::iterator it = clientList.begin();
       it != clientList.end(); ++it) 
  {
	 if ((*it)->getGame())
		(**((*it)->getGame()))->lockClient();

    if (!(*it)->getWriteBuffer()->empty()
	&& _select.fdIsset(*(*it)->getSocket(), &_fdWrite))
      sendCommandTCP(*it);

    if (_select.fdIsset(*(*it)->getSocket(), &_fdRead)
	&& !recvCommandTCP(*it))
		to_disconnect.push_back(*it);

	if ((*it)->getGame())
		(**((*it)->getGame()))->unlockClient();
  }

 for (std::list<Game *>::iterator it = gameList.begin(); it != gameList.end(); ++it)
  {
	  if ((*it)->getIsInit())
	  {
		  (*it)->lockSocket();
		  if (this->_select.fdIsset((*it)->getSocket(), &_fdRead))
		  {
	//		  std::cout << "je vais faire le fdIsset MAGGLE OMG OMG OMGGGGGGGGGGGGGGGG JE VAIS REAAAAAAAAAAAD" << std::endl;
			  this->recvFromUDP(*it);
		  }
		  (*it)->unlockSocket();
	  }
  }

  return (true);
}

bool			Network::pushCmdInRightClient(t_cmd &cmd, struct sockaddr_in &sin, Game *game)
{
	bool		end = false;

//	std::cout << "Je vais pusher dans le bon client ma gueule" << std::endl;
	game->lockClient();
	for (std::list<Client *>::iterator it = game->getClients().begin(); !end && it != game->getClients().end(); ++it)
	{
		if ((*it)->getID() == cmd.cmd[1])
		{
			memcpy(&(*it)->getFrameCMD().cmd, &cmd, sizeof(cmd));
			memcpy(&(*it)->getFrameCMD().sin, &sin, sizeof(sin));
	//		std::cout << "Command UDP associated to right client" << std::endl;
			end = true;
		}
	}
	game->unlockClient();
	if (!end)
		std::cout << "No client number " << (unsigned int)cmd.cmd[1] << " in the game " << game->getID() << std::endl;
	return end;
}

bool			Network::recvFromUDP(Game *game)
{
	unsigned int size = 0;
	struct sockaddr_in	sin;
	unsigned char		buff[512];

//	std::cout << "je vais read sur le udp maggle" << std::endl;
	if ((size = game->getSocket().recvFrom(buff, 512, &sin)) <= 0)
		return false;
	if (this->_buffer.size > 0)
    {
      if (_commandsSize[this->_buffer.cmd[0]] - this->_buffer.size < size)
	{
	  memcpy(&this->_buffer.cmd[size], buff, size);
	  this->_buffer.size += size;
	}
      else
	{
	  memcpy(&this->_buffer.cmd[size], buff, _commandsSize[this->_buffer.cmd[0]] - this->_buffer.size);
	  this->_buffer.size = _commandsSize[this->_buffer.cmd[0]];
	  this->pushCmdInRightClient(this->_buffer, sin, game);	//	  push_back in right client queue;
	  for (int i = 0; i < GREATEST_COMMAND_SIZE; ++i)
	    this->_buffer.cmd[i] = -1;
	  this->_buffer.size = 0;
	}
    }
  for (unsigned int i = 0; i < size; ++i) {
    if (_commandsSize[buff[i]] <= size - i)
      {
	memcpy(this->_buffer.cmd, &buff[i], _commandsSize[buff[i]]);
	this->_buffer.size = _commandsSize[buff[i]];
//	std::cout << "je fou une commande dans le buffer read" << std::endl;
	this->pushCmdInRightClient(this->_buffer, sin, game);// push back in right client queue 
	i += _commandsSize[buff[i]];
	this->_buffer.size = 0;
      }
    else
      {
	memcpy(this->_buffer.cmd, &buff[i], (size - 1) - i);
	this->_buffer.size =  size- i;
	i = size - 1;
      }
  }
  return true;
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



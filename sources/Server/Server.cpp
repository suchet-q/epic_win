#include		"Server.h"

Server::Server()
{
  for (int i = 0; i < 255; ++i)
   _idArray[i] = false; 
}

Server::~Server() {}

void			Server::addClient(MetaSocket<> *socket)
{
  int			id;

  if (socket == NULL)
    return ;
  for (int i = 0; i < 255; ++i)
    if (!_idArray[i]) 
      id = i;
  _clientList.push_back(new Client(id, socket));
}

void			Server::decoClient(std::list<Client *>::iterator &it)
{
  delete (*it)->getSocket();
  it = _clientList.erase(it);
}

bool			Server::initSocket(int port)
{
  if (!_socket.init(TCP)
      || !_socket.Bind("127.0.0.1", port)
      || !_socket.Listen(42))
    return false;
  return true;
}

bool			Server::loop()
{
  bool			error = false;

  while (!error) {
    _select.fdZero(&_fdWrite);
    _select.fdZero(&_fdRead);
    _select.fdSet(_socket, &_fdRead);
    for (std::list<Client *>::iterator it = _clientList.begin();
	 it != _clientList.end(); ++it) {
      _select.fdSet(*(*it)->getSocket(), &_fdRead);
      if (!(*it)->getWriteBuffer()->empty())
	_select.fdSet(*(*it)->getSocket(), &_fdWrite);
    }
    if (_select.Select(&_fdRead, &_fdWrite, 3000)) {
      if (_select.fdIsset(_socket, &_fdRead))
	addClient(_socket.Accept());
      for (std::list<Client *>::iterator it = _clientList.begin();
	   it != _clientList.end(); ++it) {
	if (!(*it)->getWriteBuffer()->empty()
	    && _select.fdIsset(*(*it)->getSocket(), &_fdWrite))
	  (*it)->sendCommand();
	if (_select.fdIsset(*(*it)->getSocket(), &_fdRead)
	    && (*it)->recvCommand())
	  decoClient(it);
      }
    }
    else
      error = true;
  }
  return true;
}

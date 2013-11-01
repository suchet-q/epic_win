#include		"Server.h"

Server::Server()
{
  for (int i = 0; i < 255; ++i)
   this->_idArray[i] = false; 
}

Server::~Server() {}

void			Server::addClient(MetaSocket<> *socket)
{
  int			id;

  for (int i = 0; i < 255; ++i)
    if (!this->_idArray[i]) 
      id = i;
  this->_clientList.push_back(new Client(id, socket));
}

bool			Server::initSocket(int port)
{
  if (!this->_socket.init(TCP)
      || !this->_socket.Bind("127.0.0.1", port)
      || !this->_socket.Listen(42))
    return false;
  return true;
}

bool			Server::loop()
{
  this->_select.fdZero(&this->_fdWrite);
  this->_select.fdZero(&this->_fdRead);
  this->_select.fdSet(this->_socket, &this->_fdRead);
  for (std::list<Client *>::iterator it = this->_clientList.begin();
       it != this->_clientList.end(); ++it) {
    this->_select.fdSet(*(*it)->getSocket(), &this->_fdRead);
    if (!(*it)->getWriteBuffer().empty())
      this->_select.fdSet(*(*it)->getSocket(), &this->_fdWrite);
  }
  this->_select.Select(&this->_fdRead, &this->_fdWrite, 500);
  if (this->_select.fdIsset(this->_socket, &this->_fdRead))
    addClient(this->_socket.Accept());
  for (std::list<Client *>::iterator it = this->_clientList.begin();
       it != this->_clientList.end(); ++it) {
    if (!(*it)->getWriteBuffer().empty() && this->_select.fdIsset(*(*it)->getSocket(), &_fdWrite))
      (*it)->sendCommand();
    if (this->_select.fdIsset(*(*it)->getSocket(), &this->_fdRead)
	&& (*it)->recvCommand())
      std::cerr << "Deco Client" << std::endl;
//      decoClient(*it);
  }
  loop();
}

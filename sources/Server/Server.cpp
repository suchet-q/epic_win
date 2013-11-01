//
// Server.cpp for airtype in /home/michel_b//epic_win
// 
// Made by geoffrey michelini
// Login   <michel_b@epitech.net>
// 
// Started on  Tue Oct 29 20:23:01 2013 geoffrey michelini
// Last update Fri Nov  1 02:05:41 2013 geoffrey michelini
//

# include		"Server.h"

Server::Server()
{
  for (int i = 0; i < 255; ++i)
    _idArray[i] = false; 
}

Server::~Server() {}

void			Server::addClient(MetaSocket<> *socket)
{
  int			id;

  for (int i = 0; i < 255; ++i)
    if (!_idArray[i]) 
      id = i;
  _clientList.push_back(new Client(id, socket));
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
  _select.fdZero(&_fdWrite);
  _select.fdZero(&_fdRead);
  _select.fdSet(_socket, &_fdRead);
  for (std::list<Client *>::iterator it = _clientList.begin();
       it != _clientList.end(); ++it) {
    _select.fdSet(*(*it)->getSocket(), &_fdRead);
    if (!(*it)->getWriteBuffer().empty())
      _select.fdSet(*(*it)->getSocket(), &_fdWrite);
  }
  _select.Select(&_fdRead, &_fdWrite, 500);
  if (_select.fdIsset(_socket, &_fdRead))
    addClient(_socket.Accept());
  for (std::list<Client *>::iterator it = _clientList.begin();
       it != _clientList.end(); ++it) {
    if (!(*it)->getWriteBuffer().empty() && _select.fdIsset(*(*it)->getSocket(), &_fdWrite))
      (*it)->sendCommand();
    if (_select.fdIsset(*(*it)->getSocket(), &_fdRead)
	&& (*it)->recvCommand())
      std::cerr << "Deco Client" << std::endl;
//      decoClient(*it);
  }
  loop();
}

void			Server::execPND(void *command, int size)
{
	/*envoie ID unique du nouveau client*/
}

void			Server::execNBP(void *command, int size)
{
	t_nbp_client	*nbp;

	nbp = reinterpret_cast<t_nbp_client *>(command);
}

void			Server::execNBL(void *command, int size)
{
	t_nbl_client	*nbl;

	nbl = reinterpret_cast<t_nbl_client *>(command);
}

void			Server::execJNL(void *command, int size)
{
	t_jnl_client	*jnl;

	jnl = reinterpret_cast<t_jnl_client *>(command);
}

void			Server::execCRL(void *command, int size)
{
	t_crl_client	*crl;

	crl = reinterpret_cast<t_crl_client *>(command);
}

void			Server::execPLJ(void *command, int size)
{
	/*indique au client qu'un nouveau player a rejoint le lobby*/
}

void			Server::execSTL(void *command, int size)
{
	t_stl_client	*stl;

	stl = reinterpret_cast<t_stl_client *>(command);
}

void			Server::execMSG(void *command, int size)
{
	t_msg_client	*msg;

	msg = reinterpret_cast<t_msg_client *>(command);
}

void			Server::execNMP(void *command, int size)
{
	t_nmp_client	*nmp;

	nmp = reinterpret_cast<t_nmp_client *>(command);
}

void			Server::execLVL(void *command, int size)
{
	t_lvl_client	*lvl;

	lvl = reinterpret_cast<t_lvl_client *>(command);
}

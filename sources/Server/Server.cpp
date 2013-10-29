//
// Server.cpp for airtype in /home/michel_b//epic_win
// 
// Made by geoffrey michelini
// Login   <michel_b@epitech.net>
// 
// Started on  Tue Oct 29 20:23:01 2013 geoffrey michelini
// Last update Tue Oct 29 22:11:29 2013 geoffrey michelini
//

# include		"Server.h"

Server::Server() {}

Server::~Server() {}

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

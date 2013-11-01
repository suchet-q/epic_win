//
// Server.h for airtype in /home/michel_b//Airtype
// 
// Made by geoffrey michelini
// Login   <michel_b@epitech.net>
// 
// Started on  Mon Oct 28 18:21:08 2013 geoffrey michelini
// Last update Fri Nov  1 01:59:46 2013 geoffrey michelini
//

#ifndef			__SERVER_H__
# define		__SERVER_H__

# include		<sys/select.h>
# include		<iostream>
# include		<string>
# include		<list>
# include		<array>

# include		"MetaSelect.h"
# include		"MetaSocket.h"
# include		"Client.h"
# include		"StructCommands.h"

class			Server
{
private:
  std::list<Client *>	_clientList;
  MetaSocket<>		_socket;
  MetaSelect<>		_select;
  struct timeval	*_tv;
  fd_set		_fdWrite;
  fd_set		_fdRead;
  std::array<bool, 255>	_idArray;

public:
  Server();
  ~Server();

  void			addClient(MetaSocket<> *);
  bool			initSocket(int port);
  bool			loop();

  void			execPND(void *command, int size);
  void			execNBP(void *command, int size);
  void			execNBL(void *command, int size);
  void			execJNL(void *command, int size);
  void			execCRL(void *command, int size);
  void			execPLJ(void *command, int size);
  void			execSTL(void *command, int size);
  void			execMSG(void *command, int size);
  void			execNMP(void *command, int size);
  void			execLVL(void *command, int size);
};

#endif

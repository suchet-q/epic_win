#pragma once

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
  void			decoClient(std::list<Client *>::iterator &it);
  bool			initSocket(int port);
  bool			loop();
};

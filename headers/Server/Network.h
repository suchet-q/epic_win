#pragma once

#include		<list>
#include		<map>
#include		<array>

#include		"MetaSocket.h"
#include		"StructCommands.h"
#include		"MetaSelect.h"
#include		"Client.h"
#include		"Resource.h"

class			Network
{
private:
  std::map<char, unsigned int>	_commandsSize;
  MetaSelect<>			_select;
  MetaSocket<>			_socket;
  fd_set			_fdWrite;
  fd_set			_fdRead;
  t_cmd				_buffer;

  bool			recvCommandTCP(Client*);
  bool			sendCommandTCP(Client*);
  bool			recvFromUDP(Game *);
  bool			pushCmdInRightClient(t_cmd &cmd, struct sockaddr_in $sin, Game *game);

public:
  Network();
  ~Network();

  bool			initSocket(int);
  void			initSelect(std::list<Client*> const&, std::list<Game *> &);
  bool			Select(unsigned int);
  bool			manageSocket(std::list<Client *>&, std::list<Game *> &, std::list<Client *> &to_disconnect, MetaSocket<> **);
};

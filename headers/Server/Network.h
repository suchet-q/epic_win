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

  bool			recvCommandTCP(Client*);
  bool			sendCommandTCP(Client*);
  void*			myMemncpy(void const*, unsigned int size) const;

public:
  Network();
  ~Network();

  bool			initSocket(int);
  void			addClient(MetaSocket<>*, std::list<Client*>&);
  void			initSelect(std::list<Client*> const&);
  bool			Select(unsigned int);
  bool			manageSocket(std::list<Client *>&, std::list<Client *> &to_disconnect, MetaSocket<> **);
};

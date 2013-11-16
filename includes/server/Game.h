#pragma once

# include		<iostream>
# include		<string>
# include		<list>
# include		<map>

# include		"ResourcesGame.h"
# include		"Client.h"
# include		"MetaMutex.h"
# include		"MetaSocket.h"
# include		"MetaThreader.hpp"
# include		"StructCommands.h"

class			Client;

class			Game
{
private:
  int				_id;
  std::list<Client *>		_clients;
  std::map<Client *, Ship *>	_clientToShip;
  MetaMutex<>			_gameClient;
  MetaMutex<>			_gameSocket;
  MetaMutex<>			_gameAttribut;
  MetaSocket<>			_socketUDP;
  MetaThreader<Game, void>	_thread;
  ResourcesGame			_resources;
  bool				_isInit;

public:
  Game(int, std::list<Client *> &);
  Game();
  ~Game();

  MetaSocket<>&		getSocket();
  ResourcesGame&	getResources();
  std::list<Client *>&	getClients();
  bool			getIsInit() const;
  int			getID();

  void			setResources(ResourcesGame const &);
  void			setID(int);

  bool			lockClient();
  bool			unlockClient();
  bool			lockSocket();
  bool			unlockSocket();
  bool			lockAttribut();
  bool			unlockAttribut();

  int			startGame(void *);
  bool			launchThread(void *arg);
  void			initPlayersShip();
  bool			init();
  void			waitAllClients();
  void			manageClientsInputs();
  void			loop();

};

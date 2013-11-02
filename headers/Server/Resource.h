#pragma once
#include	<iostream>
#include	<string>
#include	<list>
#include	<array>
#include	"Client.h"
#include	"Room.h"
#include	"MetaSocket.h"
/*#include	"MateThread.h"*/

class		Resource
{
  std::list<Client *>	_clients;
  std::list<Room *>	_rooms;
  /*	std::list<Game *>	_games;*/
  std::array<bool, 255>	_idRooms;
public:
  Resource();
  ~Resource();
  /*	std::list<Game *> const &getGame();*/
  void				addClient(int, MetaSocket<> *);
  std::list<Client *>		&getClients();
  void				createRoom(Client *);
  std::list<Room *> const	&getRooms() const;
  void				createGame(int);
};


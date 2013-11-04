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
  std::array<bool, 255>		_idArray;
  std::list<Client *>	_clients;
  std::list<Room *>	_rooms;
  /*	std::list<Game *>	_games;*/
  std::array<bool, 255>	_idRooms;
public:
  Resource();
  ~Resource();

  /*	std::list<Game *> const &getGame();*/
  std::list<Client *>		&getClients();
  bool				createRoom(Client *);
  std::list<Room *>::iterator &deleteRoom(std::list<Room *>::iterator &);
  std::list<Room *>		&getRooms();
  void				createGame(int);
};


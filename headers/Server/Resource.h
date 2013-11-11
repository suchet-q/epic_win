#pragma once
#include	<iostream>
#include	<string>
#include	<list>
#include	<array>
#include	"Client.h"
#include	"Room.h"
#include	"MetaSocket.h"
#include	"Game.h"
/*#include	"MateThread.h"*/

class		Resource
{
  std::list<Client *>	_clients;
  std::list<Client *>	_inGame;
  std::list<Client *>	_notInGame;
  std::list<Room *>		_rooms;
  std::list<Game *>		_games;
  std::array<bool, 255>	_idRooms;
  std::array<bool, 255> _idGames;
public:
  Resource();
  ~Resource();
  std::list<Game *>		&getGame();
  std::list<Game *>::iterator &deleteGame(std::list<Game *>::iterator &);
  std::list<Client *>		&getClients();
  bool				createRoom(Client *);
  std::list<Room *>::iterator &deleteRoom(std::list<Room *>::iterator &);
  std::list<Room *>		&getRooms();
  bool				checkIfGameIsPossible();
  bool				createGame(std::list<Client *> *);
  std::list<Client *> *getInGameClients();
  std::list<Client *> *getNotInGameClients();
};


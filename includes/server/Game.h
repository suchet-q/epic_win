#pragma once

#include			<iostream>
#include			<string>
#include			<list>
#include			<map>

#include			"Collisions.h"
#include			"MetaMutex.h"
#include			"MetaSocket.h"
#include			"MetaThreader.hpp"
#include			"StructCommands.h"
#include			"MetaClock.hpp"
#include			"ResourcesChecker.h"
#include			"LoadLib.hpp"
#include			"Map.h"
#include			"Decor.h"

class		Collision;

#define			REFRESH_TIME	(33000)

class				Client;

enum				Weapons
{
  MISSIL,
  LASER
};

enum				StatusInGame
{
  EMPTY,
  READY,
  DECO
};

class				Game
{
private:
	std::list<t_spawn>			_spawn;
	int							_id;
	bool						_exit;
	bool						_terminated;
	std::list<Client *>			_clients;
	std::map<Client *, Ship *>	_clientToShip;
	std::map<Entity *, Client *>		_entityToShip;
	MetaMutex<>				_gameClient;
	MetaMutex<>				_gameSocket;
	MetaMutex<>				_gameAttribut;
	MetaSocket<>				_socketUDP;
	MetaThreader<Game, void>		_thread;
	MetaClock<>				_clock;
	ResourcesGame				_resources;
	bool					_isInit;
	std::map<Client *, t_rep_client>	_repClient;
	std::map<entityType, LoadLib<> *> _instanceGetter;
	Collision				_collision;

public:
	Game(int, std::list<Client *> &);
	Game();
	~Game();

	MetaSocket<>&			getSocket();
	ResourcesGame&		getResources();
	std::list<Client *>&		getClients();
	bool				getIsInit() const;
	int				getID();
	std::map<entityType, t_tab_hit_box> *getTabHitBox();
	void				setTabHitBox(std::map<entityType, t_tab_hit_box> &);
	 std::map<entityType, LoadLib<> *> getInstanceGetter() const;

	void				setResources(ResourcesGame const &);
	void				setID(int);
	void				createEntity(t_spawn);
	bool				lockClient();
	bool				unlockClient();
	bool				lockSocket();
	bool				unlockSocket();
	bool				lockAttribut();
	bool				unlockAttribut();

	bool				getExit() const;
	void				setExit(bool);
	bool				getTerminated() const;

	bool				loadAllLib();

	int				startGame(void *);
	bool				launchThread(void *arg);
	void				initPlayersShip();
	bool				init();
	void				initBufClient();
	void				waitAllClients();
	void				manageClientsInputs();
	void				loop();
};


#pragma once
#include	<iostream>
#include	<string>
#include	<list>
#include	"Client.h"
#include	"MetaMutex.h"
#include	"ResourcesGame.h"
#include	"MetaThreader.hpp"
#include	"StructCommands.h"

class Client;
class ResourcesGame;

class Game
{
private:
	int		_id;
	ResourcesGame	_resources;
	MetaMutex<>		_gameClient;
	MetaMutex<>		_gameSocket;
	MetaMutex<>		_gameAttribut;
	MetaSocket<>	_socketUDP;
	MetaThreader<Game, void>	_thread;
	bool			_isInit;

public:
	Game(int, std::list<Client *> &);
	Game();
	~Game();
	MetaSocket<>	&getSocket();
	bool	lockClient();
	bool	unlockClient();
	bool	lockSocket();
	bool	unlockSocket();
	bool	lockAttribut();
	bool	unlockAttribut();
	bool	getIsInit() const;
	int		startGame(void *);
	bool	launchThread(void *arg);
	bool	init();
	void	setID(int);
	int		getID();
	void	setResources(ResourcesGame const &);
	ResourcesGame	&getResources();
};


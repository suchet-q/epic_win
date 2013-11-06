#pragma once
#include	<iostream>
#include	<string>
#include	<list>
#include	"client.h"
#include	"ResourcesGame.h"
#include	"MetaThreader.hpp"

class Game
{
private:
	int		_id;
	ResourcesGame*				_resources;
	MetaThreader<Game, void>*	_thread;
public:
	Game(int, std::list<Client *> *);
	Game();
	~Game();
	int		startGame(void *);
	void	setID(int);
	int		getID();
	void	setResources(ResourcesGame *);
	void	setThread(MetaThreader<Game, void> *);
	ResourcesGame	&getResources();
};


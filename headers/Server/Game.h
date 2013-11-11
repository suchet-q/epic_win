#pragma once
#include	<iostream>
#include	<string>
#include	<list>
#include	"client.h"
#include	"ResourcesGame.h"

class Game
{
private:
	int		_id;
	ResourcesGame	*_resources;
public:
	Game(int, std::list<Client *> *);
	Game();
	~Game();
	bool	startGame();
	void	setID(int);
	int		getID();
	void	setResources(ResourcesGame *);
	ResourcesGame	&getResources();
};


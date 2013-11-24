#pragma once
#include	<string.h>
#include	<fstream>
#include	<iostream>
#include	<time.h>
#include	"Ships.h"
#include	"ResourcesGame.h"
#include	"Sinus.h"
#include	"Entities.h"
#include	"Randum.h"

class Xwing : public Ship
{
private:
	int		_shoot;
	int		_nbPlayer;
	Sinus	_sinus;
	float	_xplayer;
	float	_yplayer; 
	Randum	_rand;
	bool	_first;
	float	_yStart;
public:
	Xwing();
	~Xwing();
	void update(std::list<Entity *> &entities);
};


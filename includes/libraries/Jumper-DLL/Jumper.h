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

class Jumper : public Ship
{
private:
	int		_shoot;
	int		_oldPos;
	int		_nbPlayer;
	Sinus	_sinus;
	float	_xplayer;
	float	_yplayer;
	Randum	_rand;
public:
	Jumper();
	~Jumper();
	void	update(std::list<Entity *> &entities);
};


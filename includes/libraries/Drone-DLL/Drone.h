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

class Drone : public Ship
{
private:
	float	_xplayer;
	float	_yplayer;
	int		_nbPlayer;
	int		_shoot;
	Sinus	_sinus;
	Randum	_rand;
public:
	Drone();
	~Drone();
	void update(std::list<Entity *> &entities);
};

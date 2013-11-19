#pragma once
#include	<string.h>
#include	<fstream>
#include	<iostream>
#include	"Ships.h"
#include	"ResourcesGame.h"
#include	"Sinus.h"

class Drone : Ship
{
private:
	Sinus	_sinus;
public:
	Drone();
	~Drone();
	bool update(ResourcesGame &game, unsigned int time);
};

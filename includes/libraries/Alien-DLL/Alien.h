#pragma once
#include	<string.h>
#include	<fstream>
#include	<iostream>
#include	"Ships.h"
#include	"ResourcesGame.h"
#include	"Sinus.h"

class Alien : public Ship
{
private:
	Sinus	_sinus;
public:
	Alien();
	~Alien();
	bool update(ResourcesGame &game, unsigned int time);
};


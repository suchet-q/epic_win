#pragma once
#include	<string.h>
#include	<fstream>
#include	<iostream>
#include	"Ships.h"
#include	"ResourcesGame.h"
#include	"Sinus.h"

class Xwing : Ship
{
private:
	Sinus	_sinus;
public:
	Xwing();
	~Xwing();
	bool update(ResourcesGame &game, unsigned int time);
};


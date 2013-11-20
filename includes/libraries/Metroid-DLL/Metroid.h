#pragma once
#include	<string.h>
#include	<fstream>
#include	<iostream>
#include	"Ships.h"
#include	"ResourcesGame.h"
#include	"Sinus.h"

class Metroid : public Ship
{
private:
	Sinus	_sinus;
public:
	Metroid();
	~Metroid();
	bool update(ResourcesGame &game, unsigned int time);
};


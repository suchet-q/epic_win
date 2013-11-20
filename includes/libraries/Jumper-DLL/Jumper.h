#pragma once
#include	<string.h>
#include	<fstream>
#include	<iostream>
#include	"Ships.h"
#include	"ResourcesGame.h"
#include	"Sinus.h"

class Jumper : public Ship
{
private:
	Sinus	_sinus;
public:
	Jumper();
	~Jumper();
	void update(std::list<Entity *> &);
};


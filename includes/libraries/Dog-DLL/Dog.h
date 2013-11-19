#pragma once
#include	<string.h>
#include	<fstream>
#include	<iostream>
#include	"Ships.h"
#include	"ResourcesGame.h"
#include	"Sinus.h"

class Dog : Ship
{
private:
	Sinus	_sinus;
public:
	Dog();
	~Dog();
	bool update(ResourcesGame &game, unsigned int time);
};


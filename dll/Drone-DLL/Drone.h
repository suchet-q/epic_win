#pragma once
#include	"Ship.h"

class Drone : Ship
{
public:
	Drone();
	~Drone();
	bool		checkHitBox();
};

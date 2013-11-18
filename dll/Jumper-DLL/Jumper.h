#pragma once
#include	"Ship.h"

class Jumper : Ship
{
public:
	Jumper();
	~Jumper();
	bool		checkHitBox();
};


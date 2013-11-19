#pragma once
#include	"hip.h"

class Larve : Ship
{
public:
	Larve();
	~Larve();
	bool		checkHitBox();
};


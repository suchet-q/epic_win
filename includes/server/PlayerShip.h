#pragma once

#include	"Ship.h"

class PlayerShip : public Ship
{
	void		manageInput(unsigned short input);
public:
	PlayerShip();
	~PlayerShip();
	void		update(std::list<Entity *> &);
};
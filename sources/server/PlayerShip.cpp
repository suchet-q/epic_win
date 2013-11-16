#include "PlayerShip.h"

PlayerShip::PlayerShip() : Ship() {}

PlayerShip::~PlayerShip() {}

void			PlayerShip::update(std::list<Entity *> &)
{
	if (this->_input)
		this->manageInput(this->_input);
	_coord += _vecDir;
//	shoot();
	_vecDir.set(0, 0);
	_shoot = false;
}

void			PlayerShip::manageInput(unsigned short input)
{
	_vecDir.setX(CHECK_INPUT(input, RIGHT));
	_vecDir.setY(CHECK_INPUT(input, UP));
	_vecDir.setX(_vecDir.getX() - CHECK_INPUT(input, LEFT));
	_vecDir.setY(_vecDir.getY() - CHECK_INPUT(input, DOWN));
	if (CHECK_INPUT(input, SHOOT))
		_shoot = true;
	this->_input = 0;
}
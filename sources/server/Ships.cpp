#include		"Ships.h"

Ship::Ship() {}

Ship::~Ship() {}

unsigned short			Ship::getInput() const
{
	return this->_input;
}

void					Ship::setInput(unsigned short input)
{
	this->_input = input;
}

void			Ship::setShotPool(Pool<Shot, 64>& pool) {
  _shotPool = &pool;
}

/*void			Ship::shoot()
{
  _entityList->push_back(_shotPool->getInstance());
  // set vec dir
}*/

/*void			Ship::update()
{
  _coord += _vecDir;
  shoot();
  _vecDir.set(0, 0);
  _shoot = false;
}*/



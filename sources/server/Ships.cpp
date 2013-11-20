#include		"Ships.h"

Ship::Ship() {}

Ship::~Ship() {}

unsigned short		Ship::getInput() const
{
  return this->_input;
}

void   			Ship::setInput(unsigned short input)
{
  this->_input = input;
}

void			Ship::setEntitiesPool(EntitiesPoolContainer<>& pool) {
  _entitiesPool = &pool;
}

void			Ship::update(std::list<Entity *> &entityList)
{
	_coord += _vecDir;
//	shoot();
	_vecDir.set(0, 0);
	_shoot = false;
}



/*void			Ship::update()
{
  _coord += _vecDir;
  shoot();
  _vecDir.set(0, 0);
  _shoot = false;
}*/



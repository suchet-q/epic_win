#include		"Ship.h"

Ship::Ship() {}

Ship::~Ship() {}

void			Ship::setEntityList(std::list<Entity*>* entityList) {
  _entityList = entityList;
}

void			Ship::setShotPool(Pool<Shot, 64>* pool) {
  _shotPool = pool;
}

void			Ship::shoot()
{
  _entityList->push_back(_shotPool->getInstance());
  // set vec dir
}

void			Ship::update()
{
  _coord += _vecDir;
  shoot();
  _vecDir.set(0, 0);
  _shoot = false;
}

void			Ship::manageInput(short unsigned int input)
{
  _vecDir.setX(CHECK_INPUT(input, RIGHT));
  _vecDir.setY(CHECK_INPUT(input, UP));
  _vecDir.setX(_vecDir.getX() - CHECK_INPUT(input, LEFT));
  _vecDir.setY(_vecDir.getY() - CHECK_INPUT(input, DOWN));
  if (CHECK_INPUT(input, SHOOT))
    _shoot = true;
}

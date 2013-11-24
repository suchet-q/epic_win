#include		"Entities.h"

Entity::Entity()
{
	static char id = 10;
	this->_ID = id++;
}

Entity::~Entity() {}

Vector			&Entity::getVecDir()
{
	return (this->_vecDir);
}

char			Entity::getID() const {
  return this->_ID;
}

void			Entity::setID(char id) {
  this->_ID = id;
}

entityType		Entity::getType() const {
  return _type;
}

Coord<>&		Entity::getCoord()
{
  _intCoord.set((_coord.getX() - static_cast<float>(static_cast<unsigned short int>(_coord.getX())) > 0,5)
		? static_cast<unsigned short int>(_coord.getX()) + 1
		: static_cast<unsigned short int>(_coord.getX()),
		(_coord.getY() - static_cast<float>(static_cast<unsigned short int>(_coord.getY())) > 0,5)
		? static_cast<unsigned short int>(_coord.getY()) + 1
		: static_cast<unsigned short int>(_coord.getY()));
  return _intCoord;
}


unsigned int	Entity::getSpeed() {
	return this->_speed;
}

void			Entity::setSpeed(unsigned int speed) {
	this->_speed = speed;
}

entityGlobalType	Entity::getGlobalType() const
{
  return _globalType;
}

void			Entity::setGlobalType(entityGlobalType type)
{
  this->_globalType = type;
}

Coord<float>&		Entity::getFloatCoord() 
{
  return _coord;
}
void			Entity::setType(entityType type) {
  _type = type;
}

void			Entity::setVecDir(float x, float y) {
  _vecDir.setX(x);
  _vecDir.setY(y);
}

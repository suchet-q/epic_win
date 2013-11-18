#include		"Entities.h"

Entity::Entity() {}

Entity::~Entity() {}


entityType		Entity::getType() const {
  return _type;
}

Coord<>&		Entity::getCoord()
{
	_intCoord.set((_coord.getX() - static_cast<float>(static_cast<unsigned short int>(_coord.getX())) > 0) ? static_cast<unsigned short int>(_coord.getX()) + 1 : static_cast<unsigned short int>(_coord.getX()),
		(_coord.getY() - static_cast<float>(static_cast<unsigned short int>(_coord.getY())) > 0) ? static_cast<unsigned short int>(_coord.getY()) + 1 : static_cast<unsigned short int>(_coord.getY()));
  return _intCoord;
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

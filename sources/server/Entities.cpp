#include		"Entities.h"

Entity::Entity() {}

Entity::~Entity() {}


entityType		Entity::getType() const {
  return _type;
}

Coord<>&		Entity::getCoord()
{
  _intCoord.set(static_cast<unsigned short int>(_coord.getX()),
		static_cast<unsigned short int>(_coord.getY()));
  return _intCoord;
}

Coord<float>&		Entity::getFloatCoord() 
{
	return _coord;
}
void			Entity::setType(entityType type) {
  _type = type;
}

void			Entity::setVecDir(Coord<float> const &coord) {
  _vecDir = coord;
}

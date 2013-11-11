#include		"Entity.h"

Entity::Entity() {}

Entity::~Entity() {}


entityType		Entity::getType() const {
  return _type;
}

Coord<>&		Entity::getCoord() {
  _intCoord.set(static_cast<unsigned short int>(_coord.getX()),
		static_cast<unsigned short int>(_coord.getY()));
  return _intCoord;
}

void			Entity::setVecDir(Coord<float> const &coord) {
  _vecDir = coord;
}

#include		"Shot.h"

Shot::Shot() {}

Shot::~Shot() {}

void			Shot::update(std::list<Entity *> &)
{
  this->_coord += this->_vecDir;
}

void			Shot::setLife(int life)
{
	this->_life = life;
}

int				Shot::getLife() const
{
	return this->_life;
}
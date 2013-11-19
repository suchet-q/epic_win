#include		"Shot.h"

Shot::Shot() {}

Shot::~Shot() {}

void			Shot::update(std::list<Entity *> &)
{
  this->_coord += this->_vecDir;
}

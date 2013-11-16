#include		"Shot.h"

Shot::Shot() {}

Shot::~Shot() {}

void			Shot::update(std::list<Entity *> &) {
  _coord += _vecDir;
}

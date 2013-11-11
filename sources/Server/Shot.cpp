#include		"Shot.h"

Shot::Shot() {}

Shot::~Shot() {}

void			Shot::update() {
  _coord += _vecDir;
}

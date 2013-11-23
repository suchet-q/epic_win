#include "Decor.h"

Decor::Decor() {}

Decor::~Decor() {}

void			Decor::update(std::list<Entity *> &entity)
{
	this->_vecDir.setY(-1);
}
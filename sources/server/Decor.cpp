#include "Decor.h"

Decor::Decor() {}

Decor::~Decor() {}

void			Decor::update(std::list<Entity *> &entity)
{
	this->_vecDir.setX(-1);
	this->_vecDir.setY(0);
	this->_coord += this->_vecDir;
}
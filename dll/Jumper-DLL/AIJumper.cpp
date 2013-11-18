#include "AIJumper.h"

AIJumper::AIJumper(Ship &entity)
{
	this->_ship = &entity;
}

AIJumper::AIJumper() {}


AIJumper::~AIJumper() {}

bool		AIJumper::update(ResourcesGame &game, unsigned int time)
{
	float	vecY;

	vecY = this->_sinus.getValue(this->_ship->getFloatCoord());
	/*for new  vec_coord call this->_sinus.calculNewVecX(x)
	and this->_sinus.calculNewVecY(y, vecY)*/
	if (this->_ship->getInput() == 0)
		this->_ship->setInput(LEFT);
	return (true);
}

void		AIJumper::setShip(Ship &entity)
{
	this->_ship = &entity;
}

Entity		*AIJumper::getEntity() const
{
	return (this->_ship);
}

int			AIJumper::getID()
{
	return (this->_id);
}

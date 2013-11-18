#include "AIXwing.h"

AIXwing::AIXwing(Ship &entity)
{
	this->_ship = &entity;
}

AIXwing::AIXwing() {}


AIXwing::~AIXwing() {}

bool		AIXwing::update(ResourcesGame &game, unsigned int time)
{
	float	vecY;

	vecY = this->_sinus.getValue(this->_ship->getFloatCoord());
	/*for new  vec_coord call this->_sinus.calculNewVecX(x)
	and this->_sinus.calculNewVecY(y, vecY)*/
	if (this->_ship->getInput() == 0)
		this->_ship->setInput(LEFT);
	return (true);
}

void		AIXwing::setShip(Ship &entity)
{
	this->_ship = &entity;
}

Entity		*AIXwing::getEntity() const
{
	return (this->_ship);
}

int			AIXwing::getID()
{
	return (this->_id);
}
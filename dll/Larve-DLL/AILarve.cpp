#include "AILarve.h"

AILarve::AILarve(Ship &entity)
{
	this->_ship = &entity;
}

AILarve::AILarve() {}


AILarve::~AILarve() {}

bool		AILarve::update(ResourcesGame &game, unsigned int time)
{
	float	vecY;

	vecY = this->_sinus.getValue(this->_ship->getFloatCoord());
	/*for new  vec_coord call this->_sinus.calculNewVecX(x)
	and this->_sinus.calculNewVecY(y, vecY)*/
	if (this->_ship->getInput() == 0)
		this->_ship->setInput(LEFT);
	return (true);
}

void		AILarve::setShip(Ship &entity)
{
	this->_ship = &entity;
}

Entity		*AILarve::getEntity() const
{
	return (this->_ship);
}

int			AILarve::getID()
{
	return (this->_id);
}

#include "AIMetroid.h"
AIMetroid::AIMetroid(Ship &entity)
{
	this->_ship = &entity;
}

AIMetroid::AIMetroid() {}


AIMetroid::~AIMetroid() {}

bool		AIMetroid::update(ResourcesGame &game, unsigned int time)
{
	float	vecY;

	vecY = this->_sinus.getValue(this->_ship->getFloatCoord());
	/*for new  vec_coord call this->_sinus.calculNewVecX(x)
	and this->_sinus.calculNewVecY(y, vecY)*/
	if (this->_ship->getInput() == 0)
		this->_ship->setInput(LEFT);
	return (true);
}

void		AIMetroid::setShip(Ship &entity)
{
	this->_ship = &entity;
}

Entity		*AIMetroid::getEntity() const
{
	return (this->_ship);
}

int			AIMetroid::getID()
{
	return (this->_id);
}

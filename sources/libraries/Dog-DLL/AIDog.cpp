#include "AIDog.h"

AIDog::AIDog(Ship &entity)
{
	this->_ship = &entity;
}

AIDog::AIDog() {}


AIDog::~AIDog() {}

bool		AIDog::update(ResourcesGame &game, unsigned int time)
{
	float	vecY;

	vecY = this->_sinus.getValue(this->_ship->getFloatCoord());
	/*for new  vec_coord call this->_sinus.calculNewVecX(x)
	and this->_sinus.calculNewVecY(y, vecY)*/
	if (this->_ship->getInput() == 0)
		this->_ship->setInput(LEFT);
	return (true);
}

void		AIDog::setShip(Ship &entity)
{
	this->_ship = &entity;
}

Entity		*AIDog::getEntity() const
{
	return (this->_ship);
}

int			AIDog::getID()
{
	return (this->_id);
}

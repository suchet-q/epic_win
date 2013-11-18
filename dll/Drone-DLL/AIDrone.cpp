#include "AIDrone.h"

AIDrone::AIDrone(Ship &entity)
{
	this->_ship = &entity;
}

AIDrone::AIDrone() {}


AIDrone::~AIDrone() {}

bool		AIDrone::update(ResourcesGame &game, unsigned int time)
{
	float	vecY;

	vecY = this->_sinus.getValue(this->_ship->getFloatCoord());
	/*for new  vec_coord call this->_sinus.calculNewVecX(x)
	and this->_sinus.calculNewVecY(y, vecY)*/
	if (this->_ship->getInput() == 0)
		this->_ship->setInput(LEFT);
	return (true);
}

void		AIDrone::setShip(Ship &entity)
{
	this->_ship = &entity;
}

Entity		*AIDrone::getEntity() const
{
	return (this->_ship);
}

int			AIDrone::getID()
{
	return (this->_id);
}
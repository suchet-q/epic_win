#include "AIAlien.h"

AIAlien::AIAlien(Ship &entity)
{
	this->_ship = &entity;

}

AIAlien::AIAlien() {}


AIAlien::~AIAlien() {}

bool		AIAlien::update(ResourcesGame &game, unsigned int time)
{
	float	vecY;

	vecY = this->_sinus.getValue(this->_ship->getFloatCoord());
	/*for new  vec_coord call this->_sinus.calculNewVecX(x)
	and this->_sinus.calculNewVecY(y, vecY)*/
	if (this->_ship->getInput() == 0)
		this->_ship->setInput(LEFT);
	return (true);
}

void		AIAlien::setShip(Ship &entity)
{
	this->_ship = &entity;
}

Entity		*AIAlien::getEntity() const
{
	return (this->_ship);
}

int			AIAlien::getID()
{
	return (this->_id);
}

#include "Xwing.h"

Xwing::Xwing() {}

Xwing::~Xwing() {}

bool		Xwing::update(ResourcesGame &game, unsigned int time)
{
	float	vecY;

	vecY = this->_sinus.getValue(this->_coord);
	/*for new  vec_coord call this->_sinus.calculNewVecX(x)
	and this->_sinus.calculNewVecY(y, vecY)*/
	if (this->getInput() == 0)
		this->setInput(LEFT);
	return (true);
}


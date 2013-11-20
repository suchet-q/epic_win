#include "Drone.h"

Drone::Drone() {}


Drone::~Drone() {}

void		Drone::update(std::list<Entity *> &entities)
{
	++this->_shoot;
	float	vecY;
	float	xMiss;
	float	yMiss;
	int		i = 1;
	this->_nbPlayer = 0;
	std::list<Entity *>::iterator	it = entities.begin();

	vecY = this->_sinus.getValue(this->_coord);
	this->_vecDir.setY(this->_sinus.calculNewVecY(this->_coord.getY(), vecY));
	this->_vecDir.setX(-5);
	if (this->_shoot == 120)
	{
		for (; it != entities.end() && i <= 4; ++it)
		{
			if ((*it)->getGlobalType() == PLAYER)
				++this->_nbPlayer;
			++i;
		}
		this->_nbPlayer = this->_rand.getRand(this->_nbPlayer);
		for (i = 1; it != entities.end() && i == this->_nbPlayer; ++it)
			++i;
		xMiss = this->_xplayer - this->getCoord().getX();
		yMiss = this->_yplayer - this->getCoord().getY();
		/*this->_vecDir.set(xMiss, yMiss)*/
		/*this->_vecDir.normalize(-5)*/
		this->_shoot = 0;
	}

}

extern "C"
#ifdef _WIN32
__declspec (dllexport)
#endif
Entity			*getInstance()
{
	return new Drone();
}
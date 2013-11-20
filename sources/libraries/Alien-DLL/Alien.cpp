#include "Alien.h"

Alien::Alien() {}

Alien::~Alien() {}

void		Alien::update(std::list<Entity *> &entities)
{
	++this->_shoot;
	std::list<Entity *>::iterator	it = entities.begin();
	int		i = 1;
	this->_nbPlayer  = 0;
	float	xMiss;
	float	yMiss;

	for (; it != entities.end() && i <= 4; ++it)
	{
		if ((*it)->getGlobalType() == PLAYER)
			++this->_nbPlayer;
		++i;
	}
	this->_nbPlayer = this->_rand.getRand(this->_nbPlayer);
	for (i = 1; it != entities.end() && i == this->_nbPlayer; ++it)
		++i;

	this->_xplayer = (*it)->getFloatCoord().getX();
	this->_yplayer = (*it)->getFloatCoord().getY();
	
	if (this->_xplayer < this->getCoord().getX())
		this->_vecDir.setX(-3);
	else if (this->_xplayer > this->getCoord().getX())
		this->_vecDir.setX(3);
	if (this->_yplayer < this->getCoord().getY())
		this->_vecDir.setY(-3);
	else if (this->_yplayer > this->getCoord().getY())
		this->_vecDir.setY(3);
	if (this->_shoot == 120)
	{
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
	return new Alien();
}
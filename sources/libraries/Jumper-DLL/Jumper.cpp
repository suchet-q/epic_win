#include "Jumper.h"

Jumper::Jumper()
{
	this->_oldPos = 0;
}

Jumper::~Jumper() {}

void		Jumper::update(std::list<Entity *> &entities)
{
	++this->_shoot;
	std::list<Entity *>::iterator it = entities.begin();
	int		i = 1;
	this->_nbPlayer = 0;
	float	xMiss;
	float	yMiss;
	bool	danger = false;
	int		res;

	for (; it != entities.end() && !danger; ++it)
	{
		if ((*it)->getGlobalType() == PLAYER && i <= 4)
			++this->_nbPlayer;
		if ((*it)->getGlobalType() == PLAYERMISSIL)
		{
			if ((*it)->getCoord().getY() >= this->_coord.getY()
				&& (*it)->getCoord().getY() <= (this->_coord.getY() + 57))
				danger = true;
		}
		++i;
	}
	if (danger == true)
	{
		if (this->_oldPos == 1)
		{
			this->_vecDir.setY(-8);
			this->_oldPos = 0;
		}
		else if (this->_oldPos == 2)
		{
			this->_vecDir.setY(8);
			this->_oldPos = 0;
		}
		else
		{
			res = rand() % 2 + 1;
			if (res == 1)
			{
				this->_vecDir.setY(-8);
				this->_oldPos = 1;
			}
			else
			{
				this->_vecDir.setY(8);
				this->_oldPos = 2;
			}
		}
	}
	/*else
	{
		this->_nbPlayer = rand() % this->_nbPlayer + 1;
		for (i = 1; it != entities.end() && i == this->_nbPlayer; ++it);

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
	}*/
	this->_oldPos = 0;
	if (this->_shoot == 120)
	{
		it = entities.begin();
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
Entity		*getInstance()
{
	return new Jumper();
}
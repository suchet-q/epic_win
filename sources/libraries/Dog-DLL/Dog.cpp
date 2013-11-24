#include "Dog.h"

Dog::Dog()
{
	this->_type = DOG;
	this->_globalType = MOBB;
	this->_speed = 5;
	this->_shoot = 0;
}

Dog::~Dog() {}

void		Dog::update(std::list<Entity *> &entities)
{
	++this->_shoot;
	std::list<Entity *>::iterator	it = entities.begin();
	int		i = 1;
	this->_nbPlayer = 0;
	bool	choice = false;
	Coord<float>	Miss;

	for (; it != entities.end() && i <= 4; ++it)
	{
		if ((*it)->getGlobalType() == PLAYER)
			++this->_nbPlayer;
		++i;
	}
	if (this->_nbPlayer == 0)
	{
		this->_vecDir.setX(-3);
	}
	else if (this->_nbPlayer > 0)
	{
		this->_nbPlayer = this->_rand.getRand(this->_nbPlayer);
		it = entities.begin();
		for (i = 1; it != entities.end() && i == this->_nbPlayer; ++it)
			++i;

		this->_xplayer = (*it)->getFloatCoord().getX();
		this->_yplayer = (*it)->getFloatCoord().getY();

		if (this->_yplayer < this->getCoord().getY())
		{
			this->_vecDir.setY(-3);
			choice = true;
		}
		else if (this->_yplayer > this->getCoord().getY())
		{
			this->_vecDir.setY(3);
			choice = true;
		}
		if (!choice)
		{
			if (this->_xplayer < this->getCoord().getX())
				this->_vecDir.setX(-3);
			else if (this->_xplayer > this->getCoord().getX())
				this->_vecDir.setX(3);
		}
		if (this->_shoot == 120)
		{
			Miss = (*it)->getFloatCoord() - this->getFloatCoord();
			entities.push_back(_entitiesPool->getInstance<ShotEnemy >(FIREBALL));
			entities.back()->setVecDir(Miss.getX(), Miss.getY());
			entities.back()->getVecDir().normalize();
			entities.back()->setSpeed(this->_speed);
			entities.back()->getFloatCoord().setX(this->getFloatCoord().getX() + 10);
			entities.back()->getFloatCoord().setY(this->getFloatCoord().getY());
			entities.back()->setType(FIREBALL);
			/*this->_vecDir.set(xMiss, yMiss)*/
			/*this->_vecDir.normalize(-5)*/
			this->_shoot = 0;
		}
	}
	this->_coord += this->_vecDir;
	this->_vecDir.set(0, 0);
}

extern "C"
#ifdef _WIN32
__declspec (dllexport)
#endif
Entity			*getInstance()
{
	return new Dog();
}
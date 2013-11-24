#include "Drone.h"

Drone::Drone() 
{
	this->_type = DRONE;
	this->_globalType = MOBB;
	this->_first = false;
	this->_speed = 5;
	this->_shoot = 0;
}

Drone::~Drone() {}

void		Drone::update(std::list<Entity *> &entities)
{
	float	vecY;
	Coord<float>	Miss;
	int		i = 1;
	this->_nbPlayer = 0;
	std::list<Entity *>::iterator	it = entities.begin();

	++this->_shoot;
	if (this->_first == false)
	{
		this->_yStart = this->_coord.getY();
		this->_first = true;
	}
	vecY = this->_sinus.getValue(this->_coord);
	vecY += this->_yStart;
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
		it = entities.begin();
		for (i = 1; it != entities.end() && i == this->_nbPlayer; ++it)
			++i;
		Miss = (*it)->getFloatCoord() - this->getFloatCoord();
		entities.push_back(_entitiesPool->getInstance<ShotEnemy>(FIREBALL));
		entities.back()->setVecDir(Miss.getX(), Miss.getY());
		entities.back()->getVecDir().normalize();
		entities.back()->setSpeed(this->_speed);
		entities.back()->getFloatCoord().setX(this->getFloatCoord().getX() + 10);
		entities.back()->getFloatCoord().setY(this->getFloatCoord().getY());
		entities.back()->setType(FIREBALL);
		//this->_vecDir.set(xMiss, yMiss);
		//this->_vecDir.normalize(-5);
		this->_shoot = 0;
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
	return new Drone();
}
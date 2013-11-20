#include "ShotEnemy.h"

ShotEnemy::ShotEnemy()
{
	this->_life = 1;
	this->_entityType = FIREBALL;
	this->_entityGlobalType = MOBBMISSIL;
}

ShotEnemy::~ShotEnemy() {}

entityType		ShotEnemy::getEntityType() const
{
	return (this->_entityType);
}

entityGlobalType	ShotEnemy::getEntityGlabalType() const
{
	return (this->_entityGlobalType);
}
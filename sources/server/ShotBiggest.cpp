#include "ShotBiggest.h"


ShotBiggest::ShotBiggest()
{
	this->_life = 100;
	this->_entityType = BIGGEST_SHOT;
	this->_entityGlobalType = PLAYERMISSIL;
}


ShotBiggest::~ShotBiggest() {}

entityType		ShotBiggest::getEntityType() const
{
	return (this->_entityType);
}

entityGlobalType	ShotBiggest::getEntityGlabalType() const
{
	return (this->_entityGlobalType);
}
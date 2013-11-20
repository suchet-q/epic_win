#include "ShotSmall.h"

ShotSmall::ShotSmall()
{
	this->_life = 1;
	this->_entityType = BASIC_SHOT;
	this->_entityGlobalType = PLAYERMISSIL;
}

ShotSmall::~ShotSmall() {}

entityType		ShotSmall::getEntityType() const
{
	return (this->_entityType);
}

entityGlobalType	ShotSmall::getEntityGlabalType() const
{
	return (this->_entityGlobalType);
}
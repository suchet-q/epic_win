#include "ShotBig.h"

ShotBig::ShotBig()
{
	this->_life = 3;
	this->_entityType = BIG_SHOT;
	this->_entityGlobalType = PLAYERMISSIL;
}

ShotBig::~ShotBig() {}

entityType		ShotBig::getEntityType() const
{
	return (this->_entityType);
}

entityGlobalType	ShotBig::getEntityGlabalType() const
{
	return (this->_entityGlobalType);
}
#include "ShotMedium.h"


ShotMedium::ShotMedium()
{
	this->_life = 2;
	this->_entityType = MEDIUM_SHOT;
	this->_entityGlobalType = PLAYERMISSIL;
}


ShotMedium::~ShotMedium() {}

entityType		ShotMedium::getEntityType() const
{
	return (this->_entityType);
}

entityGlobalType	ShotMedium::getEntityGlabalType() const
{
	return (this->_entityGlobalType);
}
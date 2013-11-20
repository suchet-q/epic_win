#include "ShotKikou.h"

ShotKikou::ShotKikou()
{
	this->_life = 3;
	this->_entityType = KIKOU_SHOT;
	this->_entityGlobalType = PLAYERMISSIL;
}

ShotKikou::~ShotKikou() {}

entityType		ShotKikou::getEntityType() const
{
	return (this->_entityType);
}

entityGlobalType	ShotKikou::getEntityGlabalType() const
{
	return (this->_entityGlobalType);
}

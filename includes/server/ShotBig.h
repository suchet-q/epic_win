#pragma once
#include		"Shot.h"

class ShotBig : Shot
{
private:
	unsigned int _life;
	entityType			_entityType;
	entityGlobalType	_entityGlobalType;
public:
	ShotBig();
	~ShotBig();
	entityType		getEntityType() const;
	entityGlobalType	getEntityGlabalType() const;
};


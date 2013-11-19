#pragma once
#include		"Shot.h"

class ShotSmall : Shot
{
private:
	unsigned int _life;
	entityType			_entityType;
	entityGlobalType	_entityGlobalType;
public:
	ShotSmall();
	~ShotSmall();
	entityType		getEntityType() const;
	entityGlobalType	getEntityGlabalType() const;
};


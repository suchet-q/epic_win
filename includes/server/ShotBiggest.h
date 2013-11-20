#pragma once
#include		"Shot.h"

class ShotBiggest : public Shot
{
private:
	unsigned int _life;
	entityType			_entityType;
	entityGlobalType	_entityGlobalType;
public:
	ShotBiggest();
	~ShotBiggest();
	entityType		getEntityType() const;
	entityGlobalType	getEntityGlabalType() const;
};


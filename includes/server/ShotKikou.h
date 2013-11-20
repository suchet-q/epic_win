#pragma once
#include	"Shot.h"

class ShotKikou : public Shot
{
private:
	unsigned int _life;
	entityType			_entityType;
	entityGlobalType	_entityGlobalType;
public:
	ShotKikou();
	~ShotKikou();
	entityType		getEntityType() const;
	entityGlobalType	getEntityGlabalType() const;
};


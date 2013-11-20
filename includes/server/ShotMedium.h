#pragma once
#include		"Shot.h"

class ShotMedium : public Shot
{
private:
	unsigned int _life;
	entityType			_entityType;
	entityGlobalType	_entityGlobalType;
public:
	ShotMedium();
	~ShotMedium();
	entityType		getEntityType() const;
	entityGlobalType	getEntityGlabalType() const;
};


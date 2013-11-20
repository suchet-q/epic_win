#pragma once
#include		<iostream>
#include		<string>
#include		<fstream>		
#include		"Shot.h"

class ShotEnemy : public Shot
{
private:
	unsigned int		_life;
	entityType			_entityType;
	entityGlobalType	_entityGlobalType;
public:
	ShotEnemy();
	~ShotEnemy();
	entityType		getEntityType() const;
	entityGlobalType	getEntityGlabalType() const;
};


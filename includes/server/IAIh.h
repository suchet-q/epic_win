#pragma once
#include	"ResourcesGame.h"
#include	"Entity.h"
#include	"Ship.h"

class IAI
{
public:
	virtual ~IAI();
	virtual bool		update(ResourcesGame &, unsigned int) = 0;
	virtual Entity		*getEntity() const = 0;
	virtual void		setShip(Ship &) = 0;
};
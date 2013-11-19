#pragma once
#include	"IAI.h"
#include	"Ship.h"
#include	"Sinus.h"

class AIAlien : IAI
{
private:
	Ship	*_ship;
	Sinus	_sinus;
	int		_id;
public:
	AIAlien(Ship &);
	AIAlien();
	~AIAlien();
	bool		update(ResourcesGame &, unsigned int);
	void		setShip(Ship &);
	Entity		*getEntity() const;
	int			getID();
};


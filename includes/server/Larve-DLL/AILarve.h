#pragma once
#include	"IAI.h"
#include	"Ship.h"
#include	"Sinus.h"

class AILarve : IAI
{
private:
	Ship	*_ship;
	Sinus	_sinus;
	int		_id;
public:
	AILarve(Ship &);
	AILarve();
	~AILarve();
	bool		update(ResourcesGame &, unsigned int);
	void		setShip(Ship &);
	Entity		*getEntity() const;
	int			getID();
};


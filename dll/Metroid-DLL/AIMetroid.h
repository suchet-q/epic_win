#pragma once
#include	"IAI.h"
#include	"Ship.h"
#include	"Sinus.h"

class AIMetroid : IAI
{
private:
	Ship	*_ship;
	Sinus	_sinus;
	int		_id;
public:
	AIMetroid(Ship &);
	AIMetroid();
	~AIMetroid();
	bool		update(ResourcesGame &, unsigned int);
	void		setShip(Ship &);
	Entity		*getEntity() const;
	int			getID();
};

#pragma once
#include	"IAI.h"
#include	"Ship.h"
#include	"Sinus.h"

class AIXwing : IAI
{
private:
	Ship	*_ship;
	Sinus	_sinus;
	int		_id;
public:
	AIXwing(Ship &);
	AIXwing();
	~AIXwing();
	bool		update(ResourcesGame &, unsigned int);
	void		setShip(Ship &);
	Entity		*getEntity() const;
	int			getID();
};

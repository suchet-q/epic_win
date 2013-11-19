#pragma once
#include	"IAI.h"
#include	"Ships.h"
#include	"Sinus.h"

class AIJumper : IAI
{
private:
	Ship	*_ship;
	Sinus	_sinus;
	int		_id;
public:
	AIJumper(Ship &);
	AIJumper();
	~AIJumper();
	bool		update(ResourcesGame &, unsigned int);
	void		setShip(Ship &);
	Entity		*getEntity() const;
	int			getID();
};
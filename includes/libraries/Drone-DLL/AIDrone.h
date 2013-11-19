#pragma once
#include	"IAI.h"
#include	"Ships.h"
#include	"Sinus.h"

class AIDrone : IAI
{
private:
	Ship	*_ship;
	Sinus	_sinus;
	int		_id;
public:
	AIDrone(Ship &);
	AIDrone();
	~AIDrone();
	bool		update(ResourcesGame &, unsigned int);
	void		setShip(Ship &);
	Entity		*getEntity() const;
	int			getID();
};


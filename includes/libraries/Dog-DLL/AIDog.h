#pragma once
#include	"IAI.h"
#include	"Ship.h"
#include	"Sinus.h"

class AIDog : IAI
{
private:
	Ship	*_ship;
	Sinus	_sinus;
	int		_id;
public:
	AIDog(Ship &);
	AIDog();
	~AIDog();
	bool		update(ResourcesGame &, unsigned int);
	void		setShip(Ship &);
	Entity		*getEntity() const;
	int			getID();
};


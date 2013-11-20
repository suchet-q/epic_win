#pragma once

# include		"Ships.h"

# include		"ShotSmall.h"
# include		"ShotMedium.h"
# include		"ShotBig.h"
# include		"ShotBiggest.h"


class			PlayerShip : public Ship
{
	void		manageInput(unsigned short input);
public:
	PlayerShip();
	~PlayerShip();
	void		shoot(std::list<Entity *> &entityList);
	void		update(std::list<Entity *> &);
};

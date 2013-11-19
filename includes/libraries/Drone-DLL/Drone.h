#pragma once
#include	<string.h>
#include	<fstream>
#include	<iostream>
#include	"Ships.h"
/*mettre la methode getitBox dans entities*/
class Drone : Ship
{
private:
	char	_hitBox[36][33];
	int		_x;
	int		_y;
	int		_yStart;
	int		_yEnd;
public:
	Drone();
	~Drone();
	bool		setHitBox();
	bool		checkHitBox();
	char		**getHitBox();
	int			getX();
	int			getY();
	int			getYStart();
	int			getYEnd();
};

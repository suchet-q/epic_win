#pragma once
#include	<string.h>
#include	<fstream>
#include	<iostream>
#include	"Ships.h"

class Alien : Ship
{
private:
	char	_hitBox[32][33];
	int		_x;
	int		_y;
	int		_yStart;
	int		_yEnd;
public:
	Alien();
	~Alien();
	bool		setHitBox();
	bool		checkHitBox();
	char		**getHitBox();
	int			getX();
	int			getY();
	int			getYStart();
	int			getYEnd();
};


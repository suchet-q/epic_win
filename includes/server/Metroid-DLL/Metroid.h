#pragma once
#include	<string.h>
#include	<fstream>
#include	<iostream>
#include	"Ship.h"

class Metroid : Ship
{
private:
	char	_hitBox[57][58];
	int		_x;
	int		_y;
	int		_yStart;
	int		_yEnd;
public:
	Metroid();
	~Metroid();
	bool		setHitBox();
	bool		checkHitBox();
	char		**getHitBox();
	int			getX();
	int			getY();
	int			getYStart();
	int			getYEnd();
};


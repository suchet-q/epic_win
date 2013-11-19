#pragma once
#include	<string.h>
#include	<fstream>
#include	<iostream>
#include	"Ships.h"

class Jumper : Ship
{
private:
	char	_hitBox[57][49];
	int		_x;
	int		_y;
	int		_yStart;
	int		_yEnd;
public:
	Jumper();
	~Jumper();
	bool		setHitBox();
	bool		checkHitBox();
	char		**getHitBox();
	int			getX();
	int			getY();
	int			getYStart();
	int			getYEnd();
};


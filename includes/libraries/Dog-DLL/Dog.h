#pragma once
#include	<string.h>
#include	<fstream>
#include	<iostream>
#include	"Ships.h"

class Dog : Ship
{
private:
	char	_hitBox[28][32];
	int		_x;
	int		_y;
	int		_yStart;
	int		_yEnd;
public:
	Dog();
	~Dog();
	bool		setHitBox();
	bool		checkHitBox();
	char		**getHitBox();
	int			getX();
	int			getY();
	int			getYStart();
	int			getYEnd();
};


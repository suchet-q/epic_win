#pragma once
#include	<string>
#include	<iostream>
#include	<math.h>
#include	"Coord.hpp"

class Sinus
{
public:
	Sinus();
	~Sinus();
	float		getValue(Coord<float> &coord);
	float		calculNewVecX(float);
	float		calculNewVecY(float, float);
};


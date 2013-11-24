#include "Sinus.h"

Sinus::Sinus() {}

Sinus::~Sinus() {}

float		Sinus::calculNewVecY(float y, float yVec)
{
	return (yVec - y);
}

float		Sinus::getValue(Coord<float> &coord)
{
	float result = 0;

	result = sin(coord.getX() / 50);
	result += 1;
	result *= 100;
	return (result);
}
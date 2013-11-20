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

	result = sin(coord.getX());
	result *= 50;
	return (result);
}
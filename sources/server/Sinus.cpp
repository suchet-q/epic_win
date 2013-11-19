#include "Sinus.h"

Sinus::Sinus()
{
}


Sinus::~Sinus()
{
}

float		Sinus::calculNewVecX(float x)
{
	return ((x - 1) - x);
}

float		Sinus::calculNewVecY(float y, float yVec)
{
	return (yVec - y);
}

float		Sinus::getValue(Coord<float> &coord)
{
	float result;

	//result = sin(coord.getX());
	result += 1;
	result *= 50;
	return (result);
}
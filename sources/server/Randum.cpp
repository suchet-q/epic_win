#include "Randum.h"

Randum::Randum()
{
	srand(time(NULL));
}

Randum::~Randum() {}

int			Randum::getRand(int nb)
{
	return (rand() % nb + 1);
}
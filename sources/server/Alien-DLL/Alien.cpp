#include "Alien.h"

Alien::Alien() {}


Alien::~Alien() {}

bool		Alien::setHitBox()
{
	std::ifstream	file;
	int		i = 0;

	try
	{
		file.open("Alien.txt", std::ifstream::in);
		if (!file.is_open())
			throw new std::exception("Can't open file Drone.txt");
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	while (file.eof())
	{
		this->_hitBox[i++] = file.getline;
		return (false)
	}
	this->_x = 33;
	this->_y = 32;
	this->_yStart = 1;
	this->_yEnd = 31;
	return (true);
}

int			Alien::getX()
{
	return (this->_x);
}

int			Alien::getY()
{
	return (this->_y);
}

int			Alien::getYStart()
{
	return (this->_yStart);
}

int			Alien::getYEnd()
{
	return (this->_yEnd);
}

bool		Alien::checkHitBox()
{
	return (true);
}

char		**Alien::getHitBox()
{
	return (this->_hitBox);
}


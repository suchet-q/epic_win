#include "Drone.h"

Drone::Drone() {}

Drone::~Drone() {}

bool		Drone::setHitBox()
{
	std::ifstream	file;
	int		i = 0;

	try
	{
		file.open("Drone.txt", std::ifstream::in);
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
	this->_y = 36;
	this->_yStart = 12;
	this->_yEnd = 25;
	return (true);
}

int			Drone::getX()
{
	return (this->_x);
}

int			Drone::getY()
{
	return (this->_y);
}

int			Drone::getYStart()
{
	return (this->_yStart);
}

int			Drone::getYEnd()
{
	return (this->_yEnd);
}

bool		Drone::checkHitBox()
{
	return (true);
}

char		**Drone::getHitBox()
{
	return (this->_hitBox);
}

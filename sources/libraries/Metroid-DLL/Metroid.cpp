#include "Metroid.h"


Metroid::Metroid() {}


Metroid::~Metroid() {}

bool		Metroid::setHitBox()
{
	std::ifstream	file;
	int		i = 0;

	try
	{
		file.open("Metroid.txt", std::ifstream::in);
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
	this->_x = 58;
	this->_y = 57;
	this->_yStart = 6;
	this->_yEnd = 56;
	return (true);
}

int			Metroid::getX()
{
	return (this->_x);
}

int			Metroid::getY()
{
	return (this->_y);
}

int			Metroid::getYStart()
{
	return (this->_yStart);
}

int			Metroid::getYEnd()
{
	return (this->_yEnd);
}

bool		Metroid::checkHitBox()
{
	return (true);
}

char		**Metroid::getHitBox()
{
	return (this->_hitBox);
}

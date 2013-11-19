#include "Jumper.h"


Jumper::Jumper() {}


Jumper::~Jumper() {}

bool		Jumper::setHitBox()
{
	std::ifstream	file;
	int		i = 0;

	try
	{
		file.open("Jumper.txt", std::ifstream::in);
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
	this->_x = 49;
	this->_y = 57;
	this->_yStart = 10;
	this->_yEnd = 56;
	return (true);
}

int			Jumper::getX()
{
	return (this->_x);
}

int			Jumper::getY()
{
	return (this->_y);
}

int			Jumper::getYStart()
{
	return (this->_yStart);
}

int			Jumper::getYEnd()
{
	return (this->_yEnd);
}

bool		Jumper::checkHitBox()
{
	return (true);
}

char		**Jumper::getHitBox()
{
	return (this->_hitBox);
}


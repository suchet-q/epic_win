#include "Xwing.h"

Xwing::Xwing() {}

Xwing::~Xwing() {}

bool		Xwing::setHitBox()
{
	std::ifstream	file;
	int		i = 0;

	try
	{
		file.open("Xwing.txt", std::ifstream::in);
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
	this->_x = 32;
	this->_y = 28;
	this->_yStart = 8;
	this->_yEnd = 26;
	return (true);
}

int			Xwing::getX()
{
	return (this->_x);
}

int			Xwing::getY()
{
	return (this->_y);
}

int			Xwing::getYStart()
{
	return (this->_yStart);
}

int			Xwing::getYEnd()
{
	return (this->_yEnd);
}

bool		Xwing::checkHitBox()
{
	return (true);
}

char		**Xwing::getHitBox()
{
	return (this->_hitBox);
}


#include "Dog.h"


Dog::Dog() {}


Dog::~Dog() {}

bool		Dog::setHitBox()
{
	std::ifstream	file;
	int		i = 0;

	try
	{
		file.open("Dog.txt", std::ifstream::in);
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
	this->_yStart = 2;
	this->_yEnd = 26;
	return (true);
}

int			Dog::getX()
{
	return (this->_x);
}

int			Dog::getY()
{
	return (this->_y);
}

int			Dog::getYStart()
{
	return (this->_yStart);
}

int			Dog::getYEnd()
{
	return (this->_yEnd);
}

bool		Dog::checkHitBox()
{
	return (true);
}

char		**Dog::getHitBox()
{
	return (this->_hitBox);
}

#include "PlayerShip.h"
#include <iostream>

PlayerShip::PlayerShip() : Ship() {}

PlayerShip::~PlayerShip() {}

void			PlayerShip::update(std::list<Entity *> &)
{
	if (this->_input)
		this->manageInput(this->_input);
	_coord += _vecDir;
//	std::cout << "J'AVAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAANCE" << std::endl;
	//	shoot();
	_vecDir.set(0, 0);
	_shoot = false;
}

void			PlayerShip::manageInput(unsigned short input)
{
	std::cout << "L'input = " << input << std::endl;
	_vecDir.setX(CHECK_INPUT(input, static_cast<unsigned short>(RIGHT)) * 5);
	_vecDir.setY(- CHECK_INPUT(input, static_cast<unsigned short>(UP)) * 5);
	_vecDir.setX(- CHECK_INPUT(input, static_cast<unsigned short>(LEFT) * 5));
	_vecDir.setY(CHECK_INPUT(input, static_cast<unsigned short>(DOWN)) * 5);
	if (CHECK_INPUT(input, static_cast<unsigned short>(SHOOT)))
		_shoot = true;
	std::cout << "je get l'input ma gueule , vecteur COORD : X = " << _vecDir.getX() << " Y = " << _vecDir.getY() << std::endl;
	this->_input = 0;
}
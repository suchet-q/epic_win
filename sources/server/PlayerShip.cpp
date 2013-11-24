#include "PlayerShip.h"

#include <iostream>

PlayerShip::PlayerShip() : Ship()
{
	this->_shoot = false;
	this->_globalType = PLAYER;
}

PlayerShip::~PlayerShip() {}

void			PlayerShip::resetPos()
{
	Coord<>		tmp;

	tmp.setX(static_cast<unsigned short>(_coord.getX()));
	tmp.setY(static_cast<unsigned short>(_coord.getY()));
	this->_coord.setX(static_cast<float>(_lastCoord.getX()));
	this->_coord.setY(static_cast<float>(_lastCoord.getY()));
	_lastCoord.setX(tmp.getX());
	_lastCoord.setY(tmp.getY());
}

void			PlayerShip::shoot(std::list<Entity *> &entityList)
{
	Entity		*shot;

	if ((shot = _entitiesPool->getInstance<ShotSmall>(BASIC_SHOT)) != NULL)
	{
		entityList.push_back(shot);
		entityList.back()->setVecDir(10, 0);
		entityList.back()->getFloatCoord().setX(this->getFloatCoord().getX() + 10);
		entityList.back()->getFloatCoord().setY(this->getFloatCoord().getY());
		entityList.back()->setType(BASIC_SHOT);
		entityList.back()->setGlobalType(PLAYERMISSIL);
	}
}

void			PlayerShip::update(std::list<Entity *> &entityList)
{
	Coord<>		tmp;

	if (this->_input)
		this->manageInput(this->_input);
	tmp = getCoord();
	_coord += _vecDir;
	if (getCoord() != tmp)
	{
		_lastCoord.setX(tmp.getX());
		_lastCoord.setY(tmp.getY());
	}
//	std::cout << "J'AVAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAANCE" << std::endl;
	if (_shoot)
		shoot(entityList);
	_shoot = false;
	_vecDir.set(0, 0);
	_shoot = false;
}

void			PlayerShip::manageInput(unsigned short input)
{
	//std::cout << "L'input = " << input << " la valeur de check input(RIGHT) est : " << CHECK_INPUT(input, static_cast<unsigned short>(RIGHT)) << std::endl;
	_vecDir.setX(CHECK_INPUT(input, static_cast<unsigned short>(RIGHT)) * 8.f);
	_vecDir.setX(_vecDir.getX() - (CHECK_INPUT(input, static_cast<unsigned short>(LEFT)) * 8));
	_vecDir.setY((CHECK_INPUT(input, static_cast<unsigned short>(DOWN)) * 8.f));
	_vecDir.setY(_vecDir.getY() - (CHECK_INPUT(input, static_cast<unsigned short>(UP)) * 8));
	if (CHECK_INPUT(input, static_cast<unsigned short>(SHOOT)))
		_shoot = true;
	//std::cout << "je get l'input ma gueule , vecteur COORD : X = " << _vecDir.getX() << " Y = " << _vecDir.getY() << std::endl;
	this->_input = 0;
}

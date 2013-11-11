//
// entity.cpp for entity in /home/heuzey_m//TEK3/R-TYPE
// 
// Made by mathieu heuzey
// Login   <heuzey_m@epitech.net>
// 
// Started on  Fri Nov  1 17:40:30 2013 mathieu heuzey
//

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map> 
#include <string>
#include "enum.h"
#include "explosion.h"

/* enum Move {L, R, T, D, N}; */

#define FRAMETIME (250)

class Explosion;

class Entity
{
private:
 protected:
  Explosion	*_Explosion;
  unsigned char _Type;
  int		_Id;

public:

  Entity(){};
  virtual ~Entity(){};
  virtual void SetSprite(sf::Image *) = 0;
  virtual void CutImage() = 0;
  virtual sf::Sprite &GetSprite(int, int, unsigned int, Move) = 0;
  virtual int	getId() = 0;
  virtual int	getX() = 0;
  virtual int	getY() = 0;
  virtual void	setX(int) = 0;
  virtual void	setY(int) = 0;
  virtual bool  SpriteAlive() = 0;
  virtual void		CheckEtat(Move, int, int) = 0;
  virtual sf::Sprite	&FirstState(int x, int y, int) = 0;
  virtual sf::Sprite	&CheckSize(int, int, int) = 0;
  virtual unsigned char getType() = 0;
};

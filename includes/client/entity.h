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

#define FRAMETIME (250)

class Explosion;

class Entity
{
private:
 protected:
  Explosion	*_Explosion;
  int		_Id;
  int		_Etat;
  unsigned char _Type;
  int		_X;
  int		_Y;
  int		_Status;

public:

  Entity(){};
  virtual ~Entity(){};
  /* virtual void SetSprite(sf::Image *) = 0; */
  /* virtual void CutImage() = 0; */
  virtual void	GetSprite(int, int, unsigned int, Move) = 0;
  virtual int	getId() const  = 0;
  virtual int	getX() const = 0;
  virtual int	getY() const = 0;
  virtual void	setX(int) = 0;
  virtual void	setY(int) = 0;
  virtual bool  SpriteAlive() const = 0;
  virtual void	CheckEtat(Move, int, int) = 0;
  virtual void	FirstState(int x, int y, int) = 0;
  virtual void	CheckSize(int) = 0;
  virtual int	getType() const = 0;
  virtual int	getEtat() const = 0;
  virtual int	getStatus() const = 0;
  virtual void	setId(int)  = 0;
  virtual void ResetData() = 0;
};

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map> 
#include <string>
#include "enum.h"
#include "entity.h"

/* enum class Move; */

class Explosion
{
 private:

  sf::Sprite	_ExplosionSprite;
  int		_Direction;
  int		_Id;
  unsigned int	_FrameTime;
  int		_X;
  int		_Y;

 public:

  Explosion(sf::Image *);
  ~Explosion();
  int		_Status;
  sf::Sprite	*_ExplosionAnim;
  void	SetSprite(sf::Image *);
  void	CutImage();
  sf::Sprite	&GetSprite(int, int, unsigned int, Move, int);
  int		getX();
  int		getY();
  void		setX(int);
  void		setY(int);
  int		getId();
  bool		SpriteAlive();

};

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map> 
#include <string>
#include "entity.h"

class Missil : public Entity
{
 private:

  int		_Status;
  int		_Direction;
  int		_Id;
  sf::Sprite	*_MissilAnim;
  unsigned int	_FrameTime;
  int		_X;
  int		_Y;
  Explosion	*_Explosion;
  int		_Etat;
  int		_Size;
  int		_Old;
  int		_EllapsedTime;
  unsigned char _Type;

 public:

  Missil(int id, sf::Image *);
  ~Missil();
  void	SetSprite(sf::Image *);
  void	CutImage();
  bool	        SpriteAlive();
  sf::Sprite	&GetSprite(int, int, unsigned int, Move);
  int		getX();
  int		getY();
  void		setX(int);
  void		setY(int);
  int		getId();
  void		CheckEtat(Move, int, int);
  sf::Sprite	&FirstState(int x, int y, int);
  sf::Sprite	&CheckSize(int, int, int);
  unsigned char getType();
  int		getEtat();
};

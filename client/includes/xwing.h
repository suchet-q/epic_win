#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map> 
#include <string>
#include "entity.h"

class Xwing : public Entity
{
 private:

  sf::Sprite	_XwingSprite;
  int		_Status;
  int		_Direction;
  int		_Id;
  sf::Sprite	*_XwingAnim;
  unsigned int	_FrameTime;
  int		_X;
  int		_Y;
  int		_Old;
  int		_Etat;
  int		_Size;
  int		_EllapsedTime;
  unsigned char _Type;

 public:

  Xwing(int id, sf::Image *, sf::Image *);
  ~Xwing();
  void	SetSprite(sf::Image *);
  void	CutImage();
  sf::Sprite	&GetSprite(int, int, unsigned int, Move);
  int		getX();
  int		getY();
  void		setX(int);
  void		setY(int);
  int		getId();
  bool		SpriteAlive();
  void		CheckEtat(Move, int, int);
  sf::Sprite	&FirstState(int x, int y, int);
  sf::Sprite	&CheckSize(int, int, int);
  unsigned char getType();
};

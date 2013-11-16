#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map> 
#include <string>
#include "entity.h"

class Balls : public Entity
{
 private:

  int		_Status;
  int		_Direction;
  int		_Id;
  sf::Sprite	*_BallsAnim;
  unsigned int	_FrameTime;
  int		_X;
  int		_Y;
  int		_Old;
  int		_Etat;
  int		_Size;
  Explosion	*_Explosion;
  int		_EllapsedTime;
  unsigned char _Type;

 public:

  Balls(int id, sf::Image *, sf::Image *);
  ~Balls();
  void	SetSprite(sf::Image *);
  void	CutImage();
  sf::Sprite	&GetSprite(int, int, unsigned int, Move);
  int		getX();
  int		getY();
  void		setX(int);
  void		setY(int);
  int		getId();
  void		CheckEtat(Move, int, int);
  sf::Sprite	&FirstState(int x, int, int);
  sf::Sprite	&CheckSize(int, int, int);
  bool		SpriteAlive();
  unsigned char getType();
  int		getEtat();
};

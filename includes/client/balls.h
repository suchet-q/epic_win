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
  int		_Id;
  unsigned int	_FrameTime;
  int		_X;
  int		_Y;
  int		_Old;
  int		_Etat;
  int		_Size;
  unsigned int	_EllapsedTime;
  int		_Type;

 public:

  Balls(int id);
  ~Balls();
  void		GetSprite(int, int, unsigned int, Move);
  int		getX() const;
  int		getY() const;
  void		setX(int);
  void		setY(int);
  int		getId() const;
  void		CheckEtat(Move, int, int);
  void		FirstState(int x, int, int);
  void		CheckSize(int);
  bool		SpriteAlive() const;
  int		getType() const;
  int		getEtat() const;
 int		getStatus() const;
};

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map> 
#include <string>
#include "entity.h"

class Metroid : public Entity
{
 private:

  int		_Status;
  int		_Direction;
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

  Metroid();
  ~Metroid();
  void		SetSprite(sf::Image *);
  void		CutImage();
  void		GetSprite(int, int, unsigned int, Move);
  int		getX() const;
  int		getY() const;
  void		setX(int);
  void		setY(int);
  int		getId() const;
  bool		SpriteAlive() const;
  void		CheckEtat(Move, int, int);
  void		FirstState(int x, int y, int);
  void		CheckSize(int);
  int		getType() const;
  int		getEtat() const;
  int		getStatus() const;
  void		setId(int id);
  void		ResetData();
};

/*
** ship.h for ship in /home/heuzey_m//TEK3/R-TYPE
** 
** Made by mathieu heuzey
** Login   <heuzey_m@epitech.net>
** 
** Started on  Sat Oct 26 23:19:11 2013 mathieu heuzey
** Last update Sun Nov 17 01:04:55 2013 mathieu heuzey
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map> 
#include <string>
#include "enum.h"
#include "entity.h"

enum Colors { Lblue, Pink, Green, Red, Dblue };

enum Inputs {TOP, DOWN, LEFT, RIGHT, NOTHING };

class Ship
{
 private:
  sf::Image	_TmpImg;
  sf::Sprite	_ShipSprite;
  int		_Status;
  int		_Team;
  float		_Width;
  float		_Height;
  int		_TotalWidth;
  int		_TotalHeight;
  unsigned char _Type;
  int		_Id;
  int		_Old;
  int		_X;
  int		_Y;
  Inputs	_Inputs;
  int		_Size;
  int		_Etat;
  int		_Timer;
  int		_Timer2;
 public:


  int		_FrameTime;
  int		_EllapsedTime;
  Ship(int x, int y, int team, int id);
  ~Ship();
  bool		SetSprite();
  void		GetSprite(int, int, Inputs inp, int, Move);
  void		CheckInputs(Inputs inp);
  void		CheckNothing();
  void		CheckDown();
  void		CheckTop();
  void		CheckLeftAndRight();
  unsigned char getType();
  int		getId();
  bool		SpriteAlive();
  int		getX();
  int		getY();
  Inputs	getInput();
  void		setInput(Inputs);
  void		CheckEtat(Move move, int x, int y);
  void		CheckSize(int time);
  void		FirstState(int time, Inputs inp);
  int		GetEtat();
  int		GetStatus();
};

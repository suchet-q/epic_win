/*
** ship.h for ship in /home/heuzey_m//TEK3/R-TYPE
** 
** Made by mathieu heuzey
** Login   <heuzey_m@epitech.net>
** 
** Started on  Sat Oct 26 23:19:11 2013 mathieu heuzey
** Last update Mon Nov 11 15:33:50 2013 mathieu heuzey
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
 public:


  int		_FrameTime;
  int		_EllapsedTime;
  Ship(int x, int y, int team, int id);
  ~Ship();
  void	SetSprite();
  sf::Image GetImg();
  sf::Sprite GetSprite(int, int, Inputs inp, int, Move);
  void	CheckInputs(Inputs inp);
  void  CheckNothing(std::pair<int, int> tmp);
  void	CheckDown(std::pair<int, int> tmp);
  void	CheckTop(std::pair<int, int> tmp);
  void	CheckLeftAndRight(std::pair<int, int> tmp);
  unsigned char getType();
  int		getId();
  bool		SpriteAlive();
};

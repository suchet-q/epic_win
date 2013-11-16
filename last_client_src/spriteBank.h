/*
** spritesBank.h for spriteBank in /home/heuzey_m//TEK3/R-TYPE
** 
** Made by mathieu heuzey
** Login   <heuzey_m@epitech.net>
** 
** Started on  Thu Oct 31 04:16:18 2013 mathieu heuzey
** Last update Mon Nov 11 15:38:19 2013 mathieu heuzey
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "drone.h"
#include "balls.h"
#include "entity.h"
#include "ship.h"
#include "Music.h"
#include "alien.h"
#include "dog.h"
#include "jumper.h"
#include "xwing.h"
#include "metroid.h"
#include "explosion.h"
#include "larve.h"
#include "fireball.h"
#include "missil.h"

class SpriteBank;

typedef Entity *(SpriteBank::*pfObject)(int id);

class SpriteBank
{
 private:
  sf::Image *_DroneImg;
  sf::Image *_BallsImg;
  sf::Image *_MekaImg;
  sf::Image *_AlienImg;
  sf::Image *_DogImg;
  sf::Image *_JumperImg;
  sf::Image *_XwingImg;
  sf::Image *_Metroid;
  sf::Image *_ExplosionImg;
  sf::Image *_LarveImg;
  sf::Image *_FireballImg;
  sf::Image *_MissilImg;
  pfObject  *fct;

 public:
  SpriteBank();
  ~SpriteBank();
  bool	SetImg();
  Entity	*GetDrone(int);
  Entity	*GetBalls(int);
  Entity	*GetMeka(int);
  Entity	*GetAlien(int);
  Entity	*GetDog(int);
  Entity	*GetJumper(int);
  Entity	*GetXwing(int);
  Entity	*GetMetroid(int);
  Entity	*GetLarve(int);
  Entity	*GetFireball(int);
  Entity	*GetMissil(int);
  Entity	*GetObject(unsigned char, int);
};

//
// spriteBank.cpp for spriteBank in /home/heuzey_m//TEK3/R-TYPE
// 
// Made by mathieu heuzey
// Login   <heuzey_m@epitech.net>
// 
// Started on  Thu Oct 31 04:16:24 2013 mathieu heuzey
// Last update Sat Nov 16 19:57:53 2013 mathieu heuzey
//

#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "spriteBank.h"

SpriteBank::SpriteBank()
{
  fct = new pfObject[10];
  fct[0] = &SpriteBank::GetDrone;
  fct[1] = &SpriteBank::GetAlien;
  fct[2] = &SpriteBank::GetDog;
  fct[3] = &SpriteBank::GetJumper;
  fct[4] = &SpriteBank::GetXwing;
  fct[5] = &SpriteBank::GetMetroid;
  fct[6] = &SpriteBank::GetLarve;
  fct[7] = &SpriteBank::GetFireball;
  fct[8] = &SpriteBank::GetMissil;
  fct[9] = &SpriteBank::GetBalls;
}

SpriteBank::~SpriteBank()
{
}

Entity	*SpriteBank::GetObject(unsigned char type, int id)
{
  return ((this->*fct[type])(id));
}

Entity	*SpriteBank::GetDrone(int id)
{
  Drone	*drone = new Drone(id);
  return (drone);
}

Entity	*SpriteBank::GetBalls(int id)
{
  Balls	*Ball = new Balls(id);
  return (Ball);
}

Entity	*SpriteBank::GetAlien(int id)
{
  Alien *alien = new Alien(id);
  return (alien);
}

Entity	*SpriteBank::GetDog(int id)
{
  Dog	*dog = new Dog(id);
  return (dog);
}

Entity	*SpriteBank::GetJumper(int id)
{
  Jumper *jumper = new Jumper(id);
  return (jumper);
}

Entity	*SpriteBank::GetXwing(int id)
{
  Xwing *xwing = new Xwing(id);
  return (xwing);
}

Entity	*SpriteBank::GetMetroid(int id)
{
  Metroid *metroid = new Metroid(id);
  return (metroid);
}

Entity	*SpriteBank::GetLarve(int id)
{
  Larve	*larve = new Larve(id);
  return (larve);
}

Entity	*SpriteBank::GetFireball(int id)
{
  Fireball	*fireball = new Fireball(id);
  return (fireball);
}

Entity	*SpriteBank::GetMissil(int id)
{
  Missil	*missil = new Missil(id);
  return (missil);
}

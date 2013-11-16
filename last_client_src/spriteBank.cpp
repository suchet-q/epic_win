//
// spriteBank.cpp for spriteBank in /home/heuzey_m//TEK3/R-TYPE
// 
// Made by mathieu heuzey
// Login   <heuzey_m@epitech.net>
// 
// Started on  Thu Oct 31 04:16:24 2013 mathieu heuzey
// Last update Mon Nov 11 15:29:56 2013 mathieu heuzey
//

#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "spriteBank.h"

SpriteBank::SpriteBank()
{
  this->_DroneImg = new sf::Image;
  this->_BallsImg = new sf::Image;
  this->_MekaImg = new	sf::Image;
  this->_AlienImg = new sf::Image;
  this->_DogImg = new sf::Image;
  this->_JumperImg = new sf::Image;
  this->_XwingImg = new sf::Image;
  this->_Metroid = new sf::Image;
  this->_ExplosionImg = new sf::Image;
  this->_LarveImg = new sf::Image;
  this->_FireballImg = new sf::Image;
  this->_MissilImg = new sf::Image;
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
  delete this->_DroneImg;
  delete this->_BallsImg;
  delete this->_MekaImg;
  delete this->_AlienImg;
  delete this->_DogImg;
  delete this->_JumperImg;
  delete this->_XwingImg;
  delete this->_Metroid;
  delete this->_ExplosionImg;
  delete this->_LarveImg;
  delete this->_FireballImg;
  delete this->_MissilImg;
}

Entity	*SpriteBank::GetObject(unsigned char type, int id)
{
  return ((this->*fct[type])(id));
}

bool	SpriteBank::SetImg()
{
  if (!this->_DroneImg->LoadFromFile("./sprites/r-typesheet5.png"))
    return (false);
  if (!this->_BallsImg->LoadFromFile("./sprites/r-typesheet3.png"))
    return (false);
  if (!this->_MekaImg->LoadFromFile("./sprites/r-typesheet7.png"))
    return (false);
  if (!this->_AlienImg->LoadFromFile("./sprites/r-typesheet11.png"))
    return (false);
  if (!this->_DogImg->LoadFromFile("./sprites/r-typesheet10.png"))
    return (false);
  if (!this->_JumperImg->LoadFromFile("./sprites/r-typesheet9.png"))
    return (false);
  if (!this->_XwingImg->LoadFromFile("./sprites/r-typesheet23.png"))
    return (false);
  if (!this->_Metroid->LoadFromFile("./sprites/r-typesheet24.png"))
    return (false);
  if (!this->_ExplosionImg->LoadFromFile("./sprites/r-typesheet44.png"))
    return (false);
  if (!this->_LarveImg->LoadFromFile("./sprites/r-typesheet17.png"))
    return (false);
  if (!this->_FireballImg->LoadFromFile("./sprites/r-typesheet43.png"))
    return (false);
  if (!this->_MissilImg->LoadFromFile("./sprites/r-typesheet1.png"))
    return (false);
  return true;
}

Entity	*SpriteBank::GetDrone(int id)
{
  Drone	*drone = new Drone(id, this->_DroneImg, this->_ExplosionImg);
  return (drone);
}

Entity	*SpriteBank::GetBalls(int id)
{
  Balls	*Ball = new Balls(id, this->_BallsImg, this->_ExplosionImg);
  return (Ball);
}

Entity	*SpriteBank::GetAlien(int id)
{
  Alien *alien = new Alien(id, this->_AlienImg, this->_ExplosionImg);
  return (alien);
}

Entity	*SpriteBank::GetDog(int id)
{
  Dog	*dog = new Dog(id, this->_DogImg, this->_ExplosionImg);
  return (dog);
}

Entity	*SpriteBank::GetJumper(int id)
{
  Jumper *jumper = new Jumper(id, this->_JumperImg, this->_ExplosionImg);
  return (jumper);
}

Entity	*SpriteBank::GetXwing(int id)
{
  Xwing *xwing = new Xwing(id, this->_XwingImg, this->_ExplosionImg);
  return (xwing);
}

Entity	*SpriteBank::GetMetroid(int id)
{
  Metroid *metroid = new Metroid(id, this->_Metroid, this->_ExplosionImg);
  return (metroid);
}

Entity	*SpriteBank::GetLarve(int id)
{
  Larve	*larve = new Larve(id, this->_LarveImg, this->_ExplosionImg);
  return (larve);
}

Entity	*SpriteBank::GetFireball(int id)
{
  Fireball	*fireball = new Fireball(id, this->_FireballImg);
  return (fireball);
}

Entity	*SpriteBank::GetMissil(int id)
{
  Missil	*missil = new Missil(id, this->_MissilImg);
  return (missil);
}

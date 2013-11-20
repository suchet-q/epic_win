#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map> 
#include <string>
#include "entity.h"

class Drawer;

typedef void(Drawer::*pfSprite)(int x, int y, int status);

class Drawer
{
 private:
  sf::RenderWindow	*Window;
  pfSprite	*fct;
  sf::Image *_DroneImg;
  sf::Image *_BallsImg;
  sf::Image *_AlienImg;
  sf::Image *_DogImg;
  sf::Image *_JumperImg;
  sf::Image *_XwingImg;
  sf::Image *_MetroidImg;
  sf::Image *_ExplosionImg;
  sf::Image *_LarveImg;
  sf::Image *_FireballImg;
  sf::Image *_MissilImg;
  sf::Image *_ShipImg;
  sf::Image *_LaserImg;
  sf::Image *_Decor1topImg;
  sf::Image *_Decor1downImg;
  sf::Image *_Decor2topImg;
  sf::Image *_Decor2downImg;

  sf::Sprite	*_AlienAnim;
  sf::Sprite	*_BallsAnim;
  sf::Sprite	*_DogAnim;
  sf::Sprite	*_DroneAnim;
  sf::Sprite	*_ExplosionAnim;
  sf::Sprite	*_FireballAnim;
  sf::Sprite	*_JumperAnim;
  sf::Sprite	*_LarveAnim;
  sf::Sprite	*_MetroidAnim;
  sf::Sprite	*_XwingAnim;
  sf::Sprite	*_Ship1Anim;
  sf::Sprite	*_Ship2Anim;
  sf::Sprite	*_Ship3Anim;
  sf::Sprite	*_Ship4Anim;
  sf::Sprite	*_MissilAnim;
  sf::Sprite	*_LaserAnim;
  sf::Sprite	*_DecorAnim;

  sf::Mutex	*_Mutex;
 public:
  Drawer(sf::RenderWindow * window, sf::Mutex *);
  ~Drawer();
  bool	InitSprite();
  bool	SetImg();
  void	SetSprite();
  void	CutImg();
  void	drowDrone(int x, int y, int status);
  void	drowExplosion(int x, int y, int status);
  void	drowAlien(int x, int y, int status);
  void	drowBalls(int x, int y, int status);
  void	drowDog(int x, int y, int status);
  void	drowJumper(int x, int y, int status);
  void	drowXwing(int x, int y, int status);
  void	drowMetroid(int x, int y, int status);
  void	drowLarve(int x, int y, int status);
  void	drowFireBall(int x, int y, int status);
  void	drowMissil(int x, int y, int status);
  void	drowSprite(int type, int x, int y, int status);  
  void	drowShip1(int x, int y, int status);
  void	drowShip2(int x, int y, int status);
  void	drowShip3(int x, int y, int status);
  void	drowShip4(int x, int y, int status);
  void  drowMissil2(int x, int y, int status);
  void  drowMissil3(int x, int y, int status);
  void  drowMissil4(int x, int y, int status);
  void	drowLaser(int x, int y, int status);
  void	drowDecor1Top(int x, int y, int status);
  void	drowDecor1Down(int x, int y, int status);
  void	drowDecor2Top(int x, int y, int status);
  void	drowDecor2Down(int x, int y, int status);  
};

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include "entity.h"
#include "ship.h"
#include "Drawer.h"
#include "../../includes/common/Pool.hpp"
#include "drone.h"
#include "balls.h"
#include "entity.h"
#include "ship.h"
#include "alien.h"
#include "dog.h"
#include "jumper.h"
#include "xwing.h"
#include "metroid.h"
#include "larve.h"
#include "fireball.h"
#include "missil.h"
#include "missil2.h"
#include "missil3.h"
#include "missil4.h"
#include "laser.h"
#include "decor1top.h"
#include "decor1down.h"
#include "decor2top.h"
#include "decor2down.h"

class Managewindow;

typedef Entity *(Managewindow::*pfObject)();
typedef void	(Managewindow::*pfPool)(Entity *);

class Managewindow
{
 private:
  sf::RenderWindow	*Window;
  std::list<Entity *>	_EntityList;
  std::list<sf::Sprite *> _EntitySpriteList;
  std::list<Ship   *>	_ShipList;
  std::list<sf::Sprite*> _ShipSpriteList;
  sf::Mutex		*_Mutex;
  Drawer		*_Drawer;
  Pool<Drone, 40>	_DronePool;
  Pool<Alien, 40>	_AlienPool;
  Pool<Dog, 40>		_DogPool;
  Pool<Jumper, 40>	_JumperPool;
  Pool<Xwing, 40>	_XwingPool;
  Pool<Metroid, 40>	_MetroidPool;
  Pool<Larve, 40>	_LarvePool;
  Pool<Fireball, 40>	_FireballPool;
  Pool<Missil, 40>	_MissilPool;
  Pool<Balls, 40>	_BallsPool;
  Pool<Missil2, 40>	_Missil2Pool;
  Pool<Missil3, 40>	_Missil3Pool;
  Pool<Missil4, 40>	_Missil4Pool;
  Pool<Laser, 40>	_LaserPool;
  Pool<Decor1top, 40>	_Decor1TopPool;
  Pool<Decor1down, 40>	_Decor1DownPool;
  Pool<Decor2top, 40>	_Decor2TopPool;
  Pool<Decor2down, 40>	_Decor2DownPool;
  pfObject		*fct;
  pfPool		*fct2;


 public:
  Managewindow(sf::RenderWindow *window, sf::Mutex *);
  ~Managewindow();
  /* void  DrawSomething(unsigned short id, unsigned char type, unsigned short x, unsigned short y, int time, Move move); */
  void		Update();
  void		SetShip(unsigned short id_obj, unsigned short x, unsigned short y, unsigned char type);
  void		SetDeath(unsigned short id_obj, unsigned short x, unsigned short y);
  void		SetEntity(unsigned short id_obj, unsigned short x, unsigned short y, unsigned char type);
  void		SetExplosion();
  void		SetItem(unsigned char type, unsigned short id_obj, unsigned short x, unsigned short y);
  void		SetInputs(Ship *ship, unsigned short y);
  void		CleanList();
  bool		InitDrawer();
  void		BackInPool(int type, Entity *entity);
  void		BackPoolDrone(Entity *entity);
  void		BackPoolAlien(Entity *entity);
  void		BackPoolDog(Entity *entity);
  void		BackPoolJumper(Entity *entity);
  void		BackPoolXwing(Entity *entity);
  void		BackPoolMetroid(Entity *entity);
  void		BackPoolLarve(Entity *entity);
  void		BackPoolFireball(Entity *entity);
  void		BackPoolMissil(Entity *entity);
  void		BackPoolBalls(Entity *entity);
  void		BackPoolMissil2(Entity *entity);
  void		BackPoolMissil3(Entity *entity);
  void		BackPoolMissil4(Entity *entity);
  void		BackPoolLaser(Entity *entity);
  void		BackPoolExplosion(Entity *entity);
  void		BackPoolDecor1Top(Entity *entity);
  void		BackPoolDecor1Down(Entity *entity);
  void		BackPoolDecor2Top(Entity *entity);
  void		BackPoolDecor2Down(Entity *entity);

  Entity	*GetInPool(unsigned char type);
  Entity	*GetPoolDrone();
  Entity	*GetPoolExplosion();
  Entity	*GetPoolAlien();
  Entity	*GetPoolDog();
  Entity	*GetPoolJumper();
  Entity	*GetPoolXwing();
  Entity	*GetPoolMetroid();
  Entity	*GetPoolLarve();
  Entity	*GetPoolFireball();
  Entity	*GetPoolMissil();
  Entity	*GetPoolBalls();
  Entity	*GetPoolMissil2();
  Entity	*GetPoolMissil3();
  Entity	*GetPoolMissil4();
  Entity	*GetPoolLaser();
  Entity	*GetPoolDecor1Top();
  Entity	*GetPoolDecor1Down();
  Entity	*GetPoolDecor2Top();
  Entity	*GetPoolDecor2Down();
};

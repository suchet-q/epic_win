#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include "entity.h"
#include "ship.h"
#include "spriteBank.h"

class Managewindow
{
 private:
  sf::RenderWindow	*Window;
  std::list<Entity *>	_EntityList;
  std::list<sf::Sprite> _EntitySpriteList;
  std::list<Ship   *>	_ShipList;
  std::list<sf::Sprite> _ShipSpriteList;
  SpriteBank		_SpriteBank;

 public:
  Managewindow(sf::RenderWindow *window);
  ~Managewindow();
  void  DrawSomething(unsigned short id, unsigned char type, unsigned short x, unsigned short y);
  void	Update();
};

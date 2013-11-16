#pragma once

# include		<list>
# include		<iostream>
# include		<string>

# include		"Pool.hpp"
# include		"Shot.h"
# include		"Ship.h"

class			ResourcesGame
{
private:
  Pool<Ship, 32>	_shipPool;
  Pool<Shot, 64>	_shotPool;
  std::list<Entity *>	_entityList;
  std::list<Ship *>	_shipList;

public:
  ResourcesGame();
  ~ResourcesGame();
  
  std::list<Entity *>&	getEntityList();
  std::list<Ship *>&	getShipList();

  void			createShip();
};

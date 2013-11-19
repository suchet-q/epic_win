#pragma once

# include			<list>
# include			<iostream>
# include			<string>

# include			"EntitiesPoolContainer.hpp"
# include			"Ships.h"
# include			"PlayerShip.h"
# include			"Shot.h"
# include			"Pool.hpp"

class				ResourcesGame
{
private:
  Pool<PlayerShip, 4>		_playerShipPool;
  Pool<Shot, 64>		_shotPool;
  std::list<Entity *>		_entityList;
  std::list<Ship *>		_shipList;

public:
  ResourcesGame();
  ~ResourcesGame();
  
  std::list<Entity *>&		getEntityList();
  std::list<Ship *>&		getShipList();
  Pool<Shot, 64>		&getShotPool();

  void				createPlayerShip();
};

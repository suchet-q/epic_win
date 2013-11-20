#pragma once

# include			<list>
# include			<iostream>
# include			<string>

# include			"EntitiesPoolContainer.hpp"
# include			"ShipPoolContainer.hpp"
# include			"Ships.h"
# include			"PlayerShip.h"
# include			"Shot.h"
# include			"Pool.hpp"

class				ResourcesGame
{
private:
  Pool<PlayerShip, 4>		_playerShipPool;
  EntitiesPoolContainer<>	_entitiesPool;
  ShipPoolContainer<>		_shipPool;
  std::list<Entity *>		_entityList;
  std::list<Ship *>		_shipList;

public:
  ResourcesGame();
  ~ResourcesGame();
  
  std::list<Entity *>&		getEntityList();
  std::list<Ship *>&		getShipList();
  EntitiesPoolContainer<>&	getEntitiesPool();
  ShipPoolContainer<>&		getShipPool();
  Pool<PlayerShip, 4>&		getPlayerShipPool();
  void				createPlayerShip();
};

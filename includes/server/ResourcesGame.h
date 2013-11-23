#pragma once

# include			<list>
# include			<iostream>
# include			<string>

# include			"ResourcesChecker.h"
# include			"EntitiesPoolContainer.hpp"
# include			"ShipPoolContainer.hpp"
# include			"Ships.h"
# include			"PlayerShip.h"
# include			"Shot.h"
# include			"Pool.hpp"

class				ResourcesGame
{
private:
  EntitiesPoolContainer<>		_entitiesPool;
  ShipPoolContainer<>			_shipPool;
  std::list<Entity *>			_entityList;
  std::list<Ship *>			_shipList;
  std::map<entityType, t_tab_hit_box> *_tabHitBox;

public:
  ResourcesGame();
  ~ResourcesGame();
  
  std::list<Entity *>&			getEntityList();
  std::list<Ship *>&			getShipList();
  EntitiesPoolContainer<>&		getEntitiesPool();
  ShipPoolContainer<>&			getShipPool();
  void					InitPool();
  std::map<entityType, t_tab_hit_box>&	getTabHitBox();
  void					setTabHitBox(std::map<entityType, t_tab_hit_box> *);
  bool					createPlayerShip();
};

#pragma once

# include			<list>
# include			<iostream>
# include			<string>
# include			<array>

# include			"ResourcesChecker.h"
# include			"EntitiesPoolContainer.hpp"
# include			"ShipPoolContainer.hpp"
# include			"Ships.h"
# include			"PlayerShip.h"
# include			"Shot.h"
# include			"Pool.hpp"

struct				t_rep_client
{
	char				buffer[8128];
	unsigned int			size;
	int				life;
	int				weapon;
	bool				bonus;
	int				score;
	int				hightScore;
	int				status;
};

class				ResourcesGame
{
private:
	std::array<unsigned char, 255>	_idAvailable;
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

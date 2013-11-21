#include		"ResourcesGame.h"


ResourcesGame::ResourcesGame() {}

ResourcesGame::~ResourcesGame() {}

std::map<entityType, t_tab_hit_box> &ResourcesGame::getTabHitBox()
{
	return *this->_tabHitBox;
}

void				ResourcesGame::setTabHitBox(std::map<entityType, t_tab_hit_box> *map)
{
	this->_tabHitBox = map;
}

std::list<Entity *>&	ResourcesGame::getEntityList() {
  return _entityList;
}

std::list<Ship *>&	ResourcesGame::getShipList() {
  return _shipList;
}

EntitiesPoolContainer<>& ResourcesGame::getEntitiesPool()
{
  return _entitiesPool;
}

ShipPoolContainer<>&	ResourcesGame::getShipPool()
{
  return _shipPool;
}

Pool<PlayerShip, 4>&	ResourcesGame::getPlayerShipPool()
{
  return _playerShipPool;
}

void			ResourcesGame::createPlayerShip()
{
  Ship*			newShip;

  newShip = _playerShipPool.getInstance();
  _shipList.push_back(newShip);
  _entityList.push_back(newShip);
}

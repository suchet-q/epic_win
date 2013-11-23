#include		"ResourcesGame.h"


ResourcesGame::ResourcesGame() {}

ResourcesGame::~ResourcesGame() {}

std::map<entityType, t_tab_hit_box> &ResourcesGame::getTabHitBox()
{
	return *this->_tabHitBox;
}

void			ResourcesGame::setTabHitBox(std::map<entityType, t_tab_hit_box> *map)
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

/*Pool<PlayerShip, 4>&	ResourcesGame::getPlayerShipPool()
{
  return _playerShipPool;
}*/

bool			ResourcesGame::createPlayerShip()
{
  Ship*			newShip = NULL;

  if ((newShip = dynamic_cast<Ship *>(_entitiesPool.getInstance<PlayerShip>(PLAYERS))) == NULL)
    return false;
  _shipList.push_back(newShip);
  _entityList.push_back(newShip);
  return true;
}

void			ResourcesGame::InitPool()
{
  this->_entitiesPool.addPool<PlayerShip, 4>(PLAYERS);
  this->_entitiesPool.addPool<ShotSmall, 64>(BASIC_SHOT);
  this->_entitiesPool.addPool<ShotMedium, 64>(MEDIUM_SHOT);
  this->_entitiesPool.addPool<ShotBig, 64>(BIG_SHOT);
  this->_entitiesPool.addPool<ShotBiggest, 64>(BIGGEST_SHOT);
  this->_entitiesPool.addPool<ShotEnemy, 64>(FIREBALL);
}

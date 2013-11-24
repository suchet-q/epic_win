#include		"ResourcesGame.h"


ResourcesGame::ResourcesGame()
{
	this->_idAvailable[0] = 0;
	for (unsigned int i = 1; i < 255; i++)
		this->_idAvailable[i] = true;
}

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
	this->_entitiesPool.setIdAvailable(this->_idAvailable);
	this->_shipPool.setIdAvailable(this->_idAvailable);
  this->_entitiesPool.addPool<PlayerShip, 4>(PLAYERS);
  this->_entitiesPool.addPool<ShotSmall, 512>(BASIC_SHOT);
  this->_entitiesPool.addPool<ShotMedium, 256>(MEDIUM_SHOT);
  this->_entitiesPool.addPool<ShotBig, 256>(BIG_SHOT);
  this->_entitiesPool.addPool<ShotBiggest, 256>(BIGGEST_SHOT);
  this->_entitiesPool.addPool<ShotEnemy, 256>(FIREBALL);

  this->_shipPool.addPool<64>(DRONE);
  this->_shipPool.addPool<64>(ALIEN);
  this->_shipPool.addPool<64>(XWING);
  this->_shipPool.addPool<64>(METROID);
  this->_shipPool.addPool<64>(JUMPER);
  this->_shipPool.addPool<64>(DOG);
}

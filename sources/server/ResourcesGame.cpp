#include		"ResourcesGame.h"


ResourcesGame::ResourcesGame() {}

ResourcesGame::~ResourcesGame() {}


std::list<Entity *>&	ResourcesGame::getEntityList() {
  return _entityList;
}

std::list<Ship *>&	ResourcesGame::getShipList() {
  return _shipList;
}

Pool<Shot, 64>		&ResourcesGame::getShotPool()
{
	return _shotPool;
}

void			ResourcesGame::createPlayerShip()
{
  Ship*			newShip;

  newShip = _playerShipPool.getInstance();
  _shipList.push_back(newShip);
  _entityList.push_back(newShip);
}

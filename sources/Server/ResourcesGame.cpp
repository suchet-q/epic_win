#include		"ResourcesGame.h"


ResourcesGame::ResourcesGame() {}

ResourcesGame::~ResourcesGame() {}


std::list<Entity *>&	ResourcesGame::getEntityList() {
  return _entityList;
}

std::list<Ship *>&	ResourcesGame::getShipList() {
  return _shipList;
}

void			ResourcesGame::createShip()
{
  Ship*			newShip;

  newShip = _shipPool.getInstance();
  _shipList.push_back(newShip);
  _entityList.push_back(newShip);
}

#include		"Collisions.h"

Collision::Collision()
{
  _entitiesCollisions[0] = &Collision::CollPlayerPlayer;
  _entitiesCollisions[1] = &Collision::CollPlayerMobb;
  _entitiesCollisions[2] = &Collision::CollMobbDecor;
  _entitiesCollisions[3] = &Collision::CollPlayerDecor;
  _entitiesCollisions[4] = &Collision::CollMissilDecor;
  _entitiesCollisions[5] = &Collision::CollMissilMobb;
  _entitiesCollisions[6] = &Collision::CollMissilPlayer;
}

Collision::~Collision() {}

void			Collision::setResources(ResourcesGame *resources) {
  _resources = resources;
}

void			Collision::setMapClient(std::map<Client *, t_rep_client> *mapClient) {
  this->_mapClient = mapClient;
}

void			Collision::setEntityToShip(std::map<Entity *, Client *> *entityToShip) {
  this->_entityToShip = entityToShip;
}

void			Collision::checkCollisions()
{
  checkPlayerInScreen();
  checkEntitiesCollisions();
}

void			Collision::deleteEntity(Entity *entity)
{
  if (entity->getGlobalType() == PLAYER)
    _resources->getEntitiesPool().freeInstance<PlayerShip>(entity);
  switch (entity->getType()) {
  case BASIC_SHOT :
    _resources->getEntitiesPool().freeInstance<ShotSmall>(entity);
    break;
  case MEDIUM_SHOT :
    _resources->getEntitiesPool().freeInstance<ShotMedium>(entity);
    break;
  case BIG_SHOT :
    _resources->getEntitiesPool().freeInstance<ShotBig>(entity);
    break;
  case BIGGEST_SHOT :
    _resources->getEntitiesPool().freeInstance<ShotBiggest>(entity);
    break;
  case KIKOU_SHOT :
    _resources->getEntitiesPool().freeInstance<ShotKikou>(entity);
    break;
  case FIREBALL :
    _resources->getEntitiesPool().freeInstance<ShotEnemy>(entity);
    break;
  default:
    break;
  }
}

void			Collision::manageDepop()
{
  for (std::list<Entity *>::iterator it = _resources->getEntityList().begin();
       it != _resources->getEntityList().end();) {
    switch ((*it)->getGlobalType()) {
    case MOBB:
    case MOBBMISSIL:
    case DECOR :
      if ((*it)->getCoord().getX() < -OUT_SCREEN_SIZE) {
	deleteEntity(*it);
	it = _resources->getEntityList().erase(it);
      }
      else
	++it;
      break;
    case PLAYERMISSIL :
      if ((*it)->getCoord().getX() + _resources->getTabHitBox()[(*it)->getType()].x
	  > SCREEN_WIDTH + OUT_SCREEN_SIZE) {
	_resources->getShipPool().freeInstance(*it);
	it = _resources->getEntityList().erase(it);
      }
      else
	++it;
    default:
      ++it;
      break;
    }
  }
}

void			Collision::checkPlayerInScreen()
{
  for (std::list<Ship *>::iterator it = _resources->getShipList().begin();
       it != _resources->getShipList().end(); ++it) {
    if ((*it)->getCoord().getX() < 0)
      (*it)->getCoord().setX(0);
    else if ((*it)->getCoord().getX() + _resources->getTabHitBox()[(*it)->getType()].x < SCREEN_WIDTH)
      (*it)->getCoord().setX(SCREEN_WIDTH - _resources->getTabHitBox()[(*it)->getType()].x);
    if ((*it)->getCoord().getY() < 0)
      (*it)->getCoord().setY(0);
    else if ((*it)->getCoord().getY() + _resources->getTabHitBox()[(*it)->getType()].y < SCREEN_HEIGHT)
      (*it)->getCoord().setY(SCREEN_HEIGHT - _resources->getTabHitBox()[(*it)->getType()].y);
  }
}

void			Collision::checkEntitiesCollisions()
{
  Coord<>		*a;
  Coord<>		*b;
  Coord<>		size_a;
  Coord<>		size_b;
  bool			tmp;
  std::list<Entity *>::iterator it_buf;
  

  for (std::list<Entity *>::iterator it_o = _resources->getEntityList().begin();
       it_o != _resources->getEntityList().end();) {
    _deletedOne = false;
    _deletedTwo = false;
    it_buf = it_o;
    ++it_buf;
    for (std::list<Entity *>::iterator it_t = it_buf;
	 it_t != _resources->getEntityList().end();)
      if ((*it_o)->getGlobalType() != DECOR
	  || (*it_t)->getGlobalType() != DECOR)
	{
	  a = &(*it_o)->getCoord();
	  b = &(*it_t)->getCoord();
	  _deletedOne = false;
	  _deletedTwo = false;

	  size_a.set(_resources->getTabHitBox()[(*it_o)->getType()].x,
		     _resources->getTabHitBox()[(*it_o)->getType()].y);

	  size_b.set(_resources->getTabHitBox()[(*it_t)->getType()].x,
		     _resources->getTabHitBox()[(*it_t)->getType()].y);

	  if (a->getX() < b->getX()
	      && a->getX() + size_a.getX() > b->getX()
	      && a->getY() < b->getY()
	      && a->getY() + size_a.getY() > b->getY())
	    checkEntitiesCollisionsAdvenced(it_o, it_t);
	  else if (b->getX() < a->getX()
		   && b->getX() + size_b.getX() > a->getX()
		   && b->getY() < a->getY()
		   && b->getY() + size_b.getY() > a->getY()) {
	    checkEntitiesCollisionsAdvenced(it_t, it_o);
	    tmp = _deletedOne;
	    _deletedOne = _deletedTwo;
	    _deletedTwo = tmp;
	  }
	  if (!_deletedTwo)
	    ++it_t;
	  if (it_o == _resources->getEntityList().end())
	    break;
	}
    if (!_deletedOne)
      ++it_o;
  }
}

void			Collision::checkEntitiesCollisionsAdvenced(std::list<Entity *>::iterator& it_o,
								   std::list<Entity *>::iterator& it_t)
{
  Coord<>&		a = (*it_o)->getCoord();
  Coord<>&		b = (*it_t)->getCoord();
  Coord<>		size_a;
  Coord<>		size_b;
  char**		collisionTab_a = _resources->getTabHitBox()[(*it_o)->getType()].tab;
  char**		collisionTab_b = _resources->getTabHitBox()[(*it_t)->getType()].tab;

  size_a.set(_resources->getTabHitBox()[(*it_o)->getType()].x,
	     _resources->getTabHitBox()[(*it_o)->getType()].y);

  size_b.set(_resources->getTabHitBox()[(*it_t)->getType()].x,
	     _resources->getTabHitBox()[(*it_t)->getType()].y);

  for (unsigned short int y = 0; y < size_b.getY() && y + b.getY() - a.getY() < size_a.getY(); ++y)
    for (unsigned short int x = 0; x < size_b.getX() && x + b.getX() - a.getX() < size_a.getX(); ++x)
      if (collisionTab_a[y + b.getY() - a.getY()][x + b.getX() - a.getX()] && collisionTab_a[y][x])
	collision(it_o, it_t);
}

void			Collision::collision(std::list<Entity *>::iterator& it_o,
					     std::list<Entity *>::iterator& it_t)
{
  bool			collision = false;
  bool			tmp;

  for (unsigned int i = 0; i < _entitiesCollisions.size() && !collision; ++i)
    collision = (this->*_entitiesCollisions[i])(it_o, it_t);
  if (!collision) {
    for (unsigned int i = 0; i < _entitiesCollisions.size() && !collision; ++i)
      collision = (this->*_entitiesCollisions[i])(it_t, it_o);
    tmp = _deletedOne;
    _deletedOne = _deletedTwo;
    _deletedTwo = tmp;
  }
}



bool			Collision::CollPlayerPlayer(std::list<Entity *>::iterator& it_o,
						    std::list<Entity *>::iterator& it_t)
{
  if ((*it_o)->getGlobalType() != PLAYER || (*it_t)->getGlobalType() != PLAYER)
    return false;
  (*it_o)->getFloatCoord() = (dynamic_cast<Ship *>(*it_o))->getLastCoord();
  (*it_t)->getFloatCoord() = (dynamic_cast<Ship *>(*it_t))->getLastCoord();
  return true;
}


bool			Collision::CollPlayerMobb(std::list<Entity *>::iterator& it_o,
						  std::list<Entity *>::iterator& it_t)
{
  if ((*it_o)->getGlobalType() != PLAYER || (*it_t)->getGlobalType() != MOBB)
    return false;
  this->deleteEntity((*it_o));
  it_o = this->_resources->getEntityList().erase(it_o);
  this->_deletedOne = true;
  /*event explosion*/
  return true;
}

bool			Collision::CollMobbDecor(std::list<Entity *>::iterator& it_o,
						 std::list<Entity *>::iterator& it_t)
{
  if ((*it_o)->getGlobalType() != MOBB || (*it_t)->getGlobalType() != DECOR)
    return false;
  this->deleteEntity((*it_o));
  it_o = this->_resources->getEntityList().erase(it_o);
  this->_deletedOne = true;
  /*event explosion*/
  return true;
}

bool			Collision::CollPlayerDecor(std::list<Entity *>::iterator& it_o,
						   std::list<Entity *>::iterator& it_t)
{
  Client		*tmp;

  if ((*it_o)->getGlobalType() != PLAYER || (*it_t)->getGlobalType() != DECOR)
    return false;
  tmp = (*this->_entityToShip)[(*it_o)];
  if ((*this->_mapClient)[tmp].life > 1)
    (*this->_mapClient)[tmp].life -= 1;
  else
    {
      (*this->_mapClient)[tmp].life = 0;
      this->deleteEntity((*it_o));
      it_o = this->_resources->getEntityList().erase(it_o);
      this->_deletedOne = true;
    }
  /*event explosion*/
  return true;
}

bool			Collision::CollMissilDecor(std::list<Entity *>::iterator& it_o,
						   std::list<Entity *>::iterator& it_t)
{
  Shot		*shot;

  if (((*it_o)->getGlobalType() != MOBBMISSIL && (*it_o)->getGlobalType() != PLAYERMISSIL)
      || (*it_t)->getGlobalType() != DECOR)
    return false;
  shot = dynamic_cast<Shot *>(*it_o);
  if (shot->getLife() > 1)
    shot->setLife(shot->getLife() - 1);
  else
    {
      shot->setLife(0);
      this->deleteEntity((*it_o));
      it_o = this->_resources->getEntityList().erase(it_o);
      this->_deletedOne = true;
    }
  return true;
}

bool			Collision::CollMissilMobb(std::list<Entity *>::iterator& it_o,
						  std::list<Entity *>::iterator& it_t)
{
  Shot		*shot;

  if ((*it_o)->getGlobalType() != PLAYERMISSIL || (*it_t)->getGlobalType() != MOBB)
    return false;
	
  this->deleteEntity((*it_t));
  it_t = this->_resources->getEntityList().erase(it_t);
  this->_deletedTwo = true;

  shot = dynamic_cast<Shot *>(*it_o);
  if (shot->getLife() > 1)
    shot->setLife(shot->getLife() - 1);
  else
    {
      shot->setLife(0);
      this->deleteEntity((*it_o));
      it_o = this->_resources->getEntityList().erase(it_o);
      this->_deletedOne = true;
    }
  return true;
}

bool			Collision::CollMissilPlayer(std::list<Entity *>::iterator& it_o,
						    std::list<Entity *>::iterator& it_t)
{
  Client		*tmp;

  if ((*it_o)->getGlobalType() != MOBBMISSIL || (*it_t)->getGlobalType() != PLAYER)
    return false;
	
  this->deleteEntity((*it_o));
  it_o = this->_resources->getEntityList().erase(it_o);
  this->_deletedOne = true;

  tmp = (*this->_entityToShip)[(*it_t)];
  if ((*this->_mapClient)[tmp].life > 1)
    (*this->_mapClient)[tmp].life -= 1;
  else
    {
      (*this->_mapClient)[tmp].life = 0;
      this->deleteEntity((*it_t));
      it_t = this->_resources->getEntityList().erase(it_t);
      this->_deletedTwo = true;
      this->_deletedOne = true;
    }
  return true;
}

#include		"Collisions.h"

Collision::Collision()
{
  _entitiesCollisions[0] = &Collision::CollPlayerPlayer;
  _entitiesCollisions[1] = &Collision::CollMobbMobb;
  _entitiesCollisions[2] = &Collision::CollPlayerMobb;
  _entitiesCollisions[3] = &Collision::CollMobbDecor;
  _entitiesCollisions[4] = &Collision::CollPlayerDecor;
  _entitiesCollisions[5] = &Collision::CollMissilDecor;
  _entitiesCollisions[6] = &Collision::CollMissilMobb;
  _entitiesCollisions[7] = &Collision::CollMissilPlayer;
}

Collision::~Collision() {}

void			Collision::setResources(ResourcesGame *resources) {
  _resources = resources;
}

void				Collision::setMapClient(std::map<Client *, t_rep_client> *mapClient)
{
	this->_mapClient = mapClient;
}

void				Collision::setEntityToShip(std::map<Entity *, Client *> *entityToShip)
{
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
  std::list<Entity *>::iterator it_buf;
  

  for (std::list<Entity *>::iterator it_o = _resources->getEntityList().begin();
       it_o != _resources->getEntityList().end(); ++it_o) {
    it_buf = it_o;
    ++it_buf;
    for (std::list<Entity *>::iterator it_t = it_buf;
	 it_t != _resources->getEntityList().end(); ++it_t)
      if ((*it_o)->getGlobalType() != DECOR
	  || (*it_t)->getGlobalType() != DECOR)
	{
	  a = &(*it_o)->getCoord();
	  b = &(*it_t)->getCoord();

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
		   && b->getY() + size_b.getY() > a->getY())
	    checkEntitiesCollisionsAdvenced(it_t, it_o);
	}
  }
}

void			Collision::checkEntitiesCollisionsAdvenced(std::list<Entity *>::iterator it_o,
								   std::list<Entity *>::iterator it_t)
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

void			Collision::collision(std::list<Entity *>::iterator it_o,
					     std::list<Entity *>::iterator it_t)
{
  bool			collision = false;

  for (unsigned int i = 0; i < _entitiesCollisions.size() && !collision; ++i)
    collision = (this->*_entitiesCollisions[i])(it_o, it_t);
  if (!collision)
    for (unsigned int i = 0; i < _entitiesCollisions.size() && !collision; ++i)
      collision = (this->*_entitiesCollisions[i])(it_t, it_o);
}



bool			Collision::CollPlayerPlayer(std::list<Entity *>::iterator& it_o,
						    std::list<Entity *>::iterator& it_t)
{
  if ((*it_o)->getGlobalType() != PLAYER || (*it_t)->getGlobalType() != PLAYER)
    return false;
  (*it_o)->setColision(true);
  (*it_t)->setColision(true);
  
  return true;
}

bool			Collision::CollMobbMobb(std::list<Entity *>::iterator& it_o,
						std::list<Entity *>::iterator& it_t)
{
  if ((*it_o)->getGlobalType() != MOBB || (*it_t)->getGlobalType() != MOBB)
    return false;
  /*ils se passe a traver*/
  return true;
}

bool			Collision::CollPlayerMobb(std::list<Entity *>::iterator& it_o,
						  std::list<Entity *>::iterator& it_t)
{
  if ((*it_o)->getGlobalType() != PLAYER || (*it_t)->getGlobalType() != MOBB)
    return false;
  this->_resources->getEntitiesPool().freeInstance<PlayerShip>((*it_o));
  this->_resources->getEntityList().erase(it_o);
  /*event explosion*/
  return true;
}

bool			Collision::CollMobbDecor(std::list<Entity *>::iterator& it_o,
						 std::list<Entity *>::iterator& it_t)
{
  if ((*it_o)->getGlobalType() != MOBB || (*it_t)->getGlobalType() != DECOR)
    return false;
  this->_resources->getShipPool().freeInstance((*it_o));
  this->_resources->getEntityList().erase(it_o);
  /*ne peut plus bouger*/
  return true;
}

bool			Collision::CollPlayerDecor(std::list<Entity *>::iterator& it_o,
						   std::list<Entity *>::iterator& it_t)
{
	Client		*tmp;

	if ((*it_o)->getGlobalType() != PLAYER || (*it_t)->getGlobalType() != DECOR)
		return false;
	this->_resources->getEntitiesPool().freeInstance<PlayerShip>((*it_o));
	tmp = (*this->_entityToShip)[(*it_t)];
	if ((*this->_mapClient)[tmp].life > 1)
		(*this->_mapClient)[tmp].life -= 1;
	/*verifier sa vie
	else
		dead
	this->_resources->getEntityList().erase(it_o);*/
	/*event explosion*/
	return true;
}

bool			Collision::CollMissilDecor(std::list<Entity *>::iterator& it_o,
						   std::list<Entity *>::iterator& it_t)
{
	if (((*it_o)->getGlobalType() != MOBBMISSIL && (*it_o)->getGlobalType() != PLAYERMISSIL)
		|| (*it_t)->getGlobalType() != DECOR)
			return false;
	if ((*it_o)->getGlobalType() == MOBBMISSIL)
		this->_resources->getEntitiesPool().freeInstance<ShotEnemy>((*it_o));
	else
	{
		switch ((*it_o)->getGlobalType())
		{
		case BASIC_SHOT:
			this->_resources->getEntitiesPool().freeInstance<ShotSmall>((*it_o));
			break;
		case MEDIUM_SHOT:
			this->_resources->getEntitiesPool().freeInstance<ShotMedium>((*it_o));
			break;
		case BIG_SHOT:
			this->_resources->getEntitiesPool().freeInstance<ShotBig>((*it_o));
			break;
		case BIGGEST_SHOT:
			this->_resources->getEntitiesPool().freeInstance<ShotBiggest>((*it_o));
			break;
		case KIKOU_SHOT:
			this->_resources->getEntitiesPool().freeInstance<ShotKikou>((*it_o));
			break;
		default:
			break;
		}
	}
	this->_resources->getEntityList().erase(it_o);
	/*missile detruit*/
	return true;
}

bool			Collision::CollMissilMobb(std::list<Entity *>::iterator& it_o,
						  std::list<Entity *>::iterator& it_t)
{
  if ((*it_o)->getGlobalType() != PLAYERMISSIL || (*it_t)->getGlobalType() != MOBB)
    return false;
  this->_resources->getShipPool().freeInstance((*it_t));
  this->_resources->getEntityList().erase(it_t);
  switch ((*it_o)->getGlobalType())
  {
  case BASIC_SHOT:
	  this->_resources->getEntitiesPool().freeInstance<ShotSmall>((*it_o));
	  break;
  case MEDIUM_SHOT:
	  this->_resources->getEntitiesPool().freeInstance<ShotMedium>((*it_o));
	  break;
  case BIG_SHOT:
	  this->_resources->getEntitiesPool().freeInstance<ShotBig>((*it_o));
	  break;
  case BIGGEST_SHOT:
	  this->_resources->getEntitiesPool().freeInstance<ShotBiggest>((*it_o));
	  break;
  case KIKOU_SHOT:
	  this->_resources->getEntitiesPool().freeInstance<ShotKikou>((*it_o));
	  break;
  default:
	  break;
  }
  this->_resources->getEntityList().erase(it_o);
  return true;
}

bool			Collision::CollMissilPlayer(std::list<Entity *>::iterator& it_o,
						    std::list<Entity *>::iterator& it_t)
{
	Client		*tmp;

	if ((*it_o)->getGlobalType() != MOBBMISSIL || (*it_t)->getGlobalType() != PLAYER)
		return false;
	this->_resources->getShipPool().freeInstance((*it_t));
	tmp = (*this->_entityToShip)[(*it_t)];
	if ((*this->_mapClient)[tmp].life > 1)
		(*this->_mapClient)[tmp].life -= 1;
	/*else
		dead
	this->_resources->getEntityList().erase(it_t);*/
	return true;
}

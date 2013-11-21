#include		"Collisions.h"

Collision::Collision() {}

Collision::~Collision() {}

void			Collision::setResources(ResourcesGame *resources) {
  _resources = resources;
}


void			Collision::checkCollisions()
{
  checkPlayerInScreen();
  checkEntitiesCollisions();
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
	// _ressources->getPool.freeInstance<>(*it);
	it = _resources->getEntityList().erase(it);
      }
      else
	++it;
      break;
    case PLAYERMISSIL :
		if ((*it)->getCoord().getX() + _resources->getTabHitBox()[(*it)->getType()].x
	  > SCREEN_WIDTH + OUT_SCREEN_SIZE) {
	// _ressources->getPool.freeInstance<>(*it);
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
  std::cout << "boum !" << std::endl;
}


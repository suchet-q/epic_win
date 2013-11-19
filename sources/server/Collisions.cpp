/*#include		"Collisions.h"

Collision::Collision() {}

Collision::~Collision() {}

void			Collision::setResources(ResourcesGame *resources) {
  _resources = resources;
}



void			Collision::checkCollisions();
{
  Coord<>&		a;
  Coord<>&		b;
  Coord<>&		size_a;
  Coord<>&		size_b;
  

  for (std::list<Entity *>::iterator it_o = _ressources.getEntityList().begin();
       it_o != _resources.getEntityList().end(); ++it_o)     
    for (std::list<Entity *>::iterator it_t = it + 1;
	 it_t != _resources.getEntityList().end(); ++it_t)
	if ((*it_o)->getType != LANDSCAPE
	    || (*it_t)->getType != LANDSCAPE)
	  {
	    a = (*it_o)->getCoord();
	    b = (*it_t)->getCoord();
	    size_a = (*it_o)->getSize();
	    size_b = (*it_t)->getSize();
	    if (a.getX() < b.getX()
		&& a.getX()+ size_a.getX() > b.getX()
		&& a.getY() < b.getY()
		&& a.getY()+ size_a.getY() > b.getXY())
	      checkCollisionAdvenced(it_o, it_t);
	    else if (b.getX() < a.getX()
		     && b.getX()+ size_b.getX() > a.getX()
		     && b.getY() < a.getY()
		     && b.getY()+ size_b.getY() > a.getXY())
	      checkCollisionAdvenced(it_t, it_o);
	  }
}

void			Collision::checkCollisionsAdvenced(std::list<Entity *>::iterator it_o,
							   std::list<Entity *>::iterator it_t)
{
  Coord<>&		a = (*it_o)->getCoord();
  Coord<>&		b = (*it_t)->getCoord();
  Coord<>&		size_a = (*it_o)->getSize();
  Coord<>&		size_b = (*it_t)->getSize();
  bool**		collisionTab_a = (*it_o)->getCollisionTab();
  bool**		collisionTab_b = (*it_t)->getCollisionTab();

  for (unsigned short int y = 0; y < size_b.getY() && y + b.getY() - a.getY() < size_a.getY(); ++y)
    for (unsigned short int x = 0; x < size_b.getX() && x + b.getX() - a.getX() < size_a.getX(); ++x)
      if (collisionTab_a[y + b.getY() - a.getY()][x + b.getX() - a.getX()] && collisionTab_a[y][x])
	collision(it_o, it_t);
}

void			Collision::collision(std::list<Entity *>::iterator it_o,
					     std::list<Entity *>::iterator it_t)
{

}
*/

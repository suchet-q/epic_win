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
	this->_toDelete.clear();
	checkPlayerInScreen();
	checkEntitiesCollisions();
	manageDepop();
	this->deleteList();
}

void			Collision::sendEventDeath(Entity *entity)
{
	t_aff_server	affServer;

	for (std::map<Client *, t_rep_client>::iterator it = this->_mapClient->begin(); it != this->_mapClient->end(); ++it)
	{
		affServer.id_cmd = 10;
		affServer.type = 5;
		affServer.id_obj = entity->getID();/*mettre l id dans la class entity*/;
		affServer.x = entity->getCoord().getX();
		affServer.y = entity->getCoord().getY();
		memcpy(&(*it).second.buffer[(*it).second.size], &affServer, sizeof(affServer));
		(*it).second.size += sizeof(affServer);
	}
}

void			Collision::deleteList()
{
	for (std::list<std::list<Entity *>::iterator >::iterator it = this->_toDelete.begin(); it != this->_toDelete.end(); ++it)
	{
		this->sendEventDeath((*(*it)));
		if ((*(*it))->getGlobalType() == MOBB)
			this->_resources->getShipPool().freeInstance((*(*it)));
		else
		{
			if ((*(*it))->getGlobalType() == PLAYER)
			{
				this->_resources->getShipList().remove(dynamic_cast<Ship *>(*(*it)));
				this->deleteEntity((*(*it)));
			}
		}
		this->_resources->getEntityList().erase(*it);
	}
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
  //	std::cout << "salope" << std::endl;
  for (std::list<Entity *>::iterator it = _resources->getEntityList().begin();
       it != _resources->getEntityList().end();) {
	  switch ((*it)->getGlobalType()) {
	  case MOBB:
	  case MOBBMISSIL:
	  case DECOR:
		  if ((*it)->getCoord().getX() < -OUT_SCREEN_SIZE) {
			  this->sendEventDeath(*it);
			  _resources->getShipPool().freeInstance(*it);
//			  this->_toDelete.push_back(it);
			  it = _resources->getEntityList().erase(it);
		  }
		  else
			  ++it;
		  break;
	  case PLAYERMISSIL:
		  std::cout << "Maggeeeeeeeeeeeeeeule tu vas detruire le missiiiiiiiiiiiiiiiiiiiiile" << std::endl;
		  if ((*it)->getCoord().getX() + _resources->getTabHitBox()[(*it)->getType()].x
		  > SCREEN_WIDTH + OUT_SCREEN_SIZE) {
			  this->sendEventDeath(*it);
//			  this->_toDelete.push_back(it);
			  deleteEntity(*it);
			  it = _resources->getEntityList().erase(it);
		  }
		  else
			  ++it;
		  break;
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
	if ((*it)->getFloatCoord().getX() < 0.0f)
	  (*it)->getFloatCoord().setX(0.0f);
    else if ((*it)->getFloatCoord().getX() + _resources->getTabHitBox()[(*it)->getType()].x > SCREEN_WIDTH)
      (*it)->getFloatCoord().setX(SCREEN_WIDTH - _resources->getTabHitBox()[(*it)->getType()].x);
    if ((*it)->getFloatCoord().getY() < 0.0f)
      (*it)->getFloatCoord().setY(0);
    else if ((*it)->getFloatCoord().getY() + _resources->getTabHitBox()[(*it)->getType()].y > SCREEN_HEIGHT)
      (*it)->getFloatCoord().setY(SCREEN_HEIGHT - _resources->getTabHitBox()[(*it)->getType()].y);
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
  

 // std::cout << std::endl;
  for (std::list<Entity *>::iterator it_o = _resources->getEntityList().begin();
	  it_o != _resources->getEntityList().end(); ++it_o) {
	  it_buf = it_o;
	  ++it_buf;
	  for (std::list<Entity *>::iterator it_t = it_buf;
		  it_t != _resources->getEntityList().end();++it_t)
	  if ((*it_o)->getGlobalType() != DECOR
		  || (*it_t)->getGlobalType() != DECOR)
	  {
		  a = &(*it_o)->getCoord();
		  b = &(*it_t)->getCoord();

		  if ((*it_o)->getGlobalType() == PLAYER)
			  size_a.set(_resources->getTabHitBox()[PLAYER1].x,
			  _resources->getTabHitBox()[PLAYER1].y);
		  else
			  size_a.set(_resources->getTabHitBox()[(*it_o)->getType()].x,
			  _resources->getTabHitBox()[(*it_o)->getType()].y);

		  if ((*it_t)->getGlobalType() == PLAYER)
			  size_b.set(_resources->getTabHitBox()[PLAYER1].x,
			  _resources->getTabHitBox()[PLAYER1].y);
		  else
			  size_b.set(_resources->getTabHitBox()[(*it_t)->getType()].x,
			  _resources->getTabHitBox()[(*it_t)->getType()].y);

		  if ((a->getX() <= b->getX()
			  && a->getX() + size_a.getX() >= b->getX())
			  && ((a->getY() <= b->getY()
			  && a->getY() + size_a.getY() >= b->getY())
			  || (a->getY() >= b->getY()
			  && a->getY() + size_a.getY() >= b->getY() + size_b.getY()
			  && a->getY() <= b->getY() + size_b.getY())))
		  {
			  this->_invert = false;
			  checkEntitiesCollisionsAdvenced(it_o, it_t);
		  }
		  else if ((b->getX() <= a->getX()
			  && b->getX() + size_b.getX() >= a->getX())
			  && ((b->getY() <= a->getY()
			  && b->getY() + size_b.getY() >= a->getY())
			  || (b->getY() >= a->getY()
			  && b->getY() + size_b.getY() >= a->getY() + size_a.getY()
			  && b->getY() <= a->getY() + size_a.getY())))

			  checkEntitiesCollisionsAdvenced(it_t, it_o);
	  }
  }
}

void			Collision::checkEntitiesCollisionsAdvenced(std::list<Entity *>::iterator& it_o,
								   std::list<Entity *>::iterator& it_t)
{
  Coord<>&		a = (*it_o)->getCoord();
  Coord<>&		b = (*it_t)->getCoord();
  Coord<>		size_a;
  Coord<>		size_b;
  unsigned short int	minX;
  unsigned short int	minY;
  char**		collisionTab_a;
  char**		collisionTab_b;
  bool			coll = false;
  bool			caseTwo = false;

  if ((*it_o)->getGlobalType() == PLAYER)
	  collisionTab_a = _resources->getTabHitBox()[PLAYER1].tab;
  else
	  collisionTab_a = _resources->getTabHitBox()[(*it_o)->getType()].tab;
  if ((*it_t)->getGlobalType() == PLAYER)
	  collisionTab_b = _resources->getTabHitBox()[PLAYER1].tab;
  else
	  collisionTab_b = _resources->getTabHitBox()[(*it_t)->getType()].tab;

  if ((*it_o)->getGlobalType() == PLAYER)
	  size_a.set(_resources->getTabHitBox()[PLAYER1].x,
		     _resources->getTabHitBox()[PLAYER1].y);
  else
	  size_a.set(_resources->getTabHitBox()[(*it_o)->getType()].x,
	  _resources->getTabHitBox()[(*it_o)->getType()].y);
  
  if ((*it_t)->getGlobalType() == PLAYER)
	  size_b.set(_resources->getTabHitBox()[PLAYER1].x,
		     _resources->getTabHitBox()[PLAYER1].y);
  else
	  size_b.set(_resources->getTabHitBox()[(*it_t)->getType()].x,
	  _resources->getTabHitBox()[(*it_t)->getType()].y);

  
  caseTwo = ((b.getY() >= a.getY()) ? (false) : (true));
  minX = b.getX() - a.getX();
  minY = (!caseTwo) ? (b.getY() - a.getY()) : (a.getY() - b.getY());
  if (!caseTwo) {
	  for (unsigned short int y = 0; y < size_b.getY() && y + minY < size_a.getY() && !coll; ++y)
	  for (unsigned short int x = 0; x < size_b.getX() && x + minX < size_a.getX() && !coll; ++x)
		  if (collisionTab_a[y + minY][x + minX] && collisionTab_b[y][x]);
			coll = this->collision(it_o, it_t);
  }
	else if (caseTwo) {
		for (unsigned short int y = 0; y < size_b.getY() && y < size_b.getY() - minY && !coll; ++y)
		for (unsigned short int x = 0; x < size_b.getX() && x + minX < size_a.getX() && !coll; ++x)
		if (collisionTab_a[y][x + minX] && collisionTab_b[y + minY][x])
			coll = this->collision(it_o, it_t);
     }
}

bool			Collision::collision(std::list<Entity *>::iterator& it_o,
					     std::list<Entity *>::iterator& it_t)
{
  bool			collision = false;
  bool			tmp;

  for (unsigned int i = 0; i < _entitiesCollisions.size() && !collision; ++i)
  {		
	  collision = (this->*_entitiesCollisions[i])(it_o, it_t);
  }
  if (!collision) {
    for (unsigned int i = 0; i < _entitiesCollisions.size() && !collision; ++i)
      collision = (this->*_entitiesCollisions[i])(it_t, it_o);
  }
  return collision;
}



bool			Collision::CollPlayerPlayer(std::list<Entity *>::iterator& it_o,
						    std::list<Entity *>::iterator& it_t)
{
  if ((*it_o)->getGlobalType() != PLAYER || (*it_t)->getGlobalType() != PLAYER)
    return false;
//  (*it_o)->getFloatCoord() = (dynamic_cast<Ship *>(*it_o))->getLastCoord();
//  (*it_t)->getFloatCoord() = (dynamic_cast<Ship *>(*it_t))->getLastCoord();

  (dynamic_cast<PlayerShip *>(*it_o))->resetPos();
  (dynamic_cast<PlayerShip *>(*it_t))->resetPos();
  return true;
}


bool			Collision::CollPlayerMobb(std::list<Entity *>::iterator& it_o,
						  std::list<Entity *>::iterator& it_t)
{
  if ((*it_o)->getGlobalType() != PLAYER || (*it_t)->getGlobalType() != MOBB)
    return false;
  //je suis laaaaaaaaa lol 
  this->_toDelete.push_back(it_o);
//  this->deleteEntity((*it_o));
 // it_o = this->_resources->getEntityList().erase(it_o);
  /*event explosion*/
  return true;
}

bool			Collision::CollMobbDecor(std::list<Entity *>::iterator& it_o,
						 std::list<Entity *>::iterator& it_t)
{
  if ((*it_o)->getGlobalType() != MOBB || (*it_t)->getGlobalType() != DECOR)
    return false;
  this->_toDelete.push_back(it_o);
//  this->deleteEntity((*it_o));
//  it_o = this->_resources->getEntityList().erase(it_o);
  //*event explosion*/
  return true;
}

bool			Collision::CollPlayerDecor(std::list<Entity *>::iterator& it_o,
						   std::list<Entity *>::iterator& it_t)
{
  Client		*tmp;

  if ((*it_o)->getGlobalType() != PLAYER || (*it_t)->getGlobalType() != DECOR)
    return false;
  /*tmp = (*this->_entityToShip)[(*it_o)];
  if ((*this->_mapClient)[tmp].life > 1)
    (*this->_mapClient)[tmp].life -= 1;
  else
    {
      (*this->_mapClient)[tmp].life = 0;
      this->deleteEntity((*it_o));
      it_o = this->_resources->getEntityList().erase(it_o);
      this->_deletedOne = true;
    }*/
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
 //     this->_deletedOne = true;
    }
  return true;
}

bool			Collision::CollMissilMobb(std::list<Entity *>::iterator& it_o,
	std::list<Entity *>::iterator& it_t)
{
	Shot		*shot;

	if ((*it_o)->getGlobalType() != PLAYERMISSIL || (*it_t)->getGlobalType() != MOBB)
		return false;

	this->_toDelete.remove(it_t);
	this->_toDelete.push_back(it_t);
//	  this->deleteEntity((*it_t));
//	  it_t = this->_resources->getEntityList().erase(it_t);
//	  this->_deletedTwo = true;

	  shot = dynamic_cast<Shot *>(*it_o);
	  if (shot->getLife() > 1)
		  shot->setLife(shot->getLife() - 1);
	  else
	  {
		  shot->setLife(0);
		  this->_toDelete.remove(it_o);
		  this->_toDelete.push_back(it_o);
//		  this->deleteEntity((*it_o));
//		  it_o = this->_resources->getEntityList().erase(it_o);
//		  this->_deletedOne = true;
	  }
	  //it_o = it_t;
//	  if (it_t != _resources->getEntityList().end())

  return true;
}

bool			Collision::CollMissilPlayer(std::list<Entity *>::iterator& it_o,
						    std::list<Entity *>::iterator& it_t)
{
  Client		*tmp;

  if ((*it_o)->getGlobalType() != MOBBMISSIL || (*it_t)->getGlobalType() != PLAYER)
    return false;
	
  this->_toDelete.push_back(it_o);
  for (std::list<std::list<Entity *>::iterator>::iterator it = this->_toDelete.begin(); it != this->_toDelete.end(); ++it)
  if (*it == it_o) {
	  std::cout << "etron" << std::endl;
	  system("pause");
  }
//	this->deleteEntity((*it_o));
//	it_o = this->_resources->getEntityList().erase(it_o);
//	this->_deletedOne = true;

	  tmp = (*this->_entityToShip)[(*it_t)];
	if ((*this->_mapClient)[tmp].life > 1)
	 (*this->_mapClient)[tmp].life -= 1;
	else
		{
		(*this->_mapClient)[tmp].life = 0;
		this->_toDelete.push_back(it_t);
		for (std::list<std::list<Entity *>::iterator>::iterator it = this->_toDelete.begin(); it != this->_toDelete.end(); ++it)
		if (*it == it_o) {
			std::cout << "etron sur le sol" << std::endl;
			system("pause");
		}
//		this->deleteEntity((*it_t));
//		it_t = this->_resources->getEntityList().erase(it_t);
//		this->_deletedTwo = true;
//		this->_deletedOne = true;
    }
  return true;
}

#pragma once

#include			"ResourcesGame.h"

#include			"PlayerShip.h"
#include			"ShotSmall.h"
#include			"ShotMedium.h"
#include			"ShotBig.h"
#include			"ShotBiggest.h"
#include			"ShotKikou.h"

class				Client;
class				Game;

#define				SCREEN_WIDTH		(1024)
#define				SCREEN_HEIGHT		(768)
#define				OUT_SCREEN_SIZE		(500)	

class				Collision;

typedef bool			(Collision::*entitiesColl)(std::list<Entity *>::iterator&,
							   std::list<Entity *>::iterator&);

class				Collision
{
private:
  ResourcesGame*					_resources;
  std::array<entitiesColl, 7>		_entitiesCollisions;
  std::map<Client *, t_rep_client>	*_mapClient;
  std::map<Entity *, Client *>		*_entityToShip;
  std::list<std::list<Entity *>::iterator > _toDelete;
  bool								_invert;


public:
  Collision();
  ~Collision();

  void				deleteList();
  void				sendEventDeath(Entity *entity);
  void				setMapClient(std::map<Client *, t_rep_client> *);
  void				setEntityToShip(std::map<Entity *, Client *> *);
  void				setResources(ResourcesGame *resources);
  void				manageDepop();
  void				checkPlayerInScreen();
  void				checkCollisions();
  void				deleteEntity(Entity *entitiy);
  void				checkEntitiesCollisions();
  void				checkEntitiesCollisionsAdvenced(std::list<Entity *>::iterator& it_o,
								std::list<Entity *>::iterator& it_t);
  bool				collision(std::list<Entity *>::iterator& it_o,
					  std::list<Entity *>::iterator& it_t);
  
  bool				CollPlayerPlayer(std::list<Entity *>::iterator& it_o,
						 std::list<Entity *>::iterator& it_t);
  bool				CollPlayerMobb(std::list<Entity *>::iterator& it_o,
					       std::list<Entity *>::iterator& it_t);
  bool				CollMobbDecor(std::list<Entity *>::iterator& it_o,
					      std::list<Entity *>::iterator& it_t);
  bool				CollPlayerDecor(std::list<Entity *>::iterator& it_o,
						std::list<Entity *>::iterator& it_t);
  bool				CollMissilDecor(std::list<Entity *>::iterator& it_o,
						std::list<Entity *>::iterator& it_t);
  bool				CollMissilMobb(std::list<Entity *>::iterator& it_o,
					       std::list<Entity *>::iterator& it_t);
  bool				CollMissilPlayer(std::list<Entity *>::iterator& it_o,
						 std::list<Entity *>::iterator& it_t);
};

#include			"Clients.h"

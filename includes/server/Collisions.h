#pragma once

#include			"ResourcesGame.h"

#define			SCREEN_WIDTH		(1024)
#define			SCREEN_HEIGHT		(768)
#define			OUT_SCREEN_SIZE		(500)	

class				Collision
{
private:
  ResourcesGame			*_resources;

public:
  Collision();
  ~Collision();

  void				setResources(ResourcesGame *resources);
  void				manageDepop();
  void				checkPlayerInScreen();
  void				checkCollisions();
  void				checkEntitiesCollisions();
  void				checkEntitiesCollisionsAdvenced(std::list<Entity *>::iterator it_o,
							std::list<Entity *>::iterator it_t);
  void				collision(std::list<Entity *>::iterator it_o,
					  std::list<Entity *>::iterator it_t);
};

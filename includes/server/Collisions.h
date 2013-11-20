#pragma once

# include			"ResourcesGame.h"

# define			SCREEN_WIDTH		(1024)
# define			SRCEEN_HEIGHT		(768)
# define			OUT_SCREEN_SIZE		(500)	

class				Collision
{
private:
  ResourcesGame			*_resources;

public:
  Collision();
  ~Collision();

  void				setResources(ResourcesGame *resources);
  
  void				checkCollisions();
  void				checkEntitiesCollisions();
  void				checkCollisionsAdvenced(std::list<Entity *>::iterator it_o,
							std::list<Entity *>::iterator it_t);
  void				collision(std::list<Entity *>::iterator it_o,
					  std::list<Entity *>::iterator it_t);
};

#pragma once

# include			"ResourcesGame.h"

class				Collision
{
private:
  ResourcesGame			*_resources;

public:
  Collision();
  ~Collision();

  void				setResources(ResourcesGame *resources);
  
  void				checkCollisions();
  void				checkCollisionsAdvenced(std::list<Entity *>::iterator it_o,
							std::list<Entity *>::iterator it_t);
  void				collision(std::list<Entity *>::iterator it_o,
					  std::list<Entity *>::iterator it_t);
};

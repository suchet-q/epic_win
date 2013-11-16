#pragma once

# include		<list>

# include		"Entity.h"
# include		"Pool.hpp"
# include		"Shot.h"

# define		LEFT			(1)
# define		RIGHT			(2)
# define		UP			(4)
# define		DOWN			(8)
# define		SHOOT			(16)

# define		CHECK_INPUT(in, st)	((in & st == st) ? (1) : (0))

class			Ship : public Entity
{
private:
  bool			_shoot;
  std::list<Entity*>*	_entityList;
  Pool<Shot, 64>*	_shotPool;

public:
  Ship();
  ~Ship();

  void			setEntityList(std::list<Entity *>* entityList);
  void			setShotPool(Pool<Shot, 64>* pool);

  void			update();
  void			shoot();
  void			manageInput(short unsigned int imput);
};

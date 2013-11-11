#pragma once

# include		<list>

# include		"Entity.h"

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

public:
  Ship();
  ~Ship();

  void			setEntityList(std::list<Entity *>* entityList);

  void			update();
  void			manageInput(short unsigned int imput);
};

#pragma once

#include		<list>

#include		"Entities.h"
#include		"Shot.h"
#include		"Pool.hpp"

#define		LEFT			(1)
#define		RIGHT			(2)
#define		UP				(4)
#define		DOWN			(8)
#define		SHOOT			(16)

# define		CHECK_INPUT(in, st)	((in & st) ? (1) : (0))

class			Ship : public Entity
{
protected:
  bool			_shoot;
  Pool<Shot, 64>*	_shotPool;
  unsigned short	_input;

public:
  Ship();
  virtual ~Ship();

  void			setShotPool(Pool<Shot, 64>& pool);
  unsigned short	getInput() const;
  void				setInput(unsigned short);
  virtual void			update(std::list<Entity *> &);
};

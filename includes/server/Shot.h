#pragma once

# include		"Entities.h"

class			Shot : public Entity
{
protected:
	int			_life;
public:
  Shot();
  ~Shot();

  void			update(std::list<Entity *> &);
  void			setLife(int);
  int			getLife() const;
};

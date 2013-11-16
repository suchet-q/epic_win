#pragma once

# include		"Entity.h"

class			Shot : public Entity
{
public:
  Shot();
  ~Shot();

  void			update(std::list<Entity *> &);
};

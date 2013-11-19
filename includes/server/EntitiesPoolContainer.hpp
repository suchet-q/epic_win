#pragma once

# include			<map>

# include			"Pool.hpp"
# include			"Entities.h"

# include			"PlayerShip.h"
//# include			"Alien.h"
//# include			"Dog.h"
//# include			"Drone.h"
//# include			"Jumper.h"
//# include			"Larve.h"
//# include			"Metroid.h"
//# include			"PlayerShip.h"

class				EntitiesPoolContainer
{
private:
  std::map<entityType, IPool *>	_poolMap;

public:
  EntitiesPoolContainer() {}
  ~EntitiesPoolContainer() {}

  template <typename T, unsigned int SIZE>
  bool				addPool(entityType type)
  {
    if (_poolMap[type])
      return false;
    _poolMap[type] = new Pool<T, SIZE>;
    return true;
  }

  template <typename T>
  T*				getInstance(entityType type)
  {
    APool<T>*			pool;
    
    pool = dynamic_cast<APool<T>* >(_poolMap[type]);
    return pool.getInstance();
  }
  
  template <typename T>
  void				freeInstance(T* instance)
  {
    APool<T>*			pool;
    
    pool = dynamic_cast<APool<T>* >(_poolMap[type]);
    return pool.freeInstance();
  }
};

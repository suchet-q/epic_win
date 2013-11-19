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
  std::map<entityType, IPool<Entity *> *>	_poolMap;
  std::map<entityType, unsigned int>		_poolSizeMap;
  //  std::map<entityType, >			_poolMap;

public:
  EntitiesPoolContainer() {}

  ~EntitiesPoolContainer()
  {
    for (std::map<entityType, IPool<Entity* >* >::iterator it = _poolMap.begin();
	 it != _poolMap.end(); ++it)
      {
	for (unsigned int i = 0; i < _poolSizeMap[(*it).first]; ++i)
	  delete *((*it).second->getElem(i));
	delete (*it).second;
      }
  }

  template <typename T, unsigned int SIZE>
  bool				addPool(entityType type)
  {
    Pool<T *, SIZE>*		pool;

    if (_poolMap[type])
      return false;
    pool = new Pool<T *, SIZE>;
    //for (unsigned int i = 0; i < SIZE; ++i)
      //      pool->getArray()[i] = 
    _poolMap[type] = pool;
    _poolSizeMap[type] = SIZE;
    return true;
  }

  template <typename T>
  T*				getInstance(entityType type) {
    return *(_poolMap[type]->getInstance());
  }
  
  template <typename T>
  void				freeInstance(T* instance) {
    _poolMap[instance->getType()].freeInstance();
  }
};

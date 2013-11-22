#pragma once

# include			<map>

# include			"Pool.hpp"
# include			"Entities.h"
# include			"LoadLib.hpp"

template <typename T = Entity>
class				ShipPoolContainer
{
private:
  std::map<entityType, IPool<Entity *> *>	_poolMap;
  std::map<entityType, unsigned int>		_poolSizeMap;
  std::map<entityType, LoadLib<>* >*		_libMap;

public:
  ShipPoolContainer() {}

  ~ShipPoolContainer()
  {
    for (std::map<entityType, IPool<Entity* >* >::iterator it = _poolMap.begin();
	 it != _poolMap.end(); ++it)
      {
	for (unsigned int i = 0; i < _poolSizeMap[(*it).first]; ++i)
	  delete *((*it).second->getElem(i));
	delete (*it).second;
      }
  }

  void				setLibMap(std::map<entityType, LoadLib<>* >& libMap) {
    _libMap = &libMap;
  }

  template <unsigned int SIZE>
  bool				addPool(entityType type)
  {
    Pool<T *, SIZE>*		pool;

    if (_poolMap[type])
      return false;
    pool = new Pool<T *, SIZE>;
    for (unsigned int i = 0; i < SIZE; ++i)

      pool->getArray()[i] = (*_libMap)[type]->getInstance<Entity>();
    _poolMap[type] = pool;
    _poolSizeMap[type] = SIZE;
    return true;
  }

  T*				getInstance(entityType type) {
    return *(_poolMap[type]->getInstance());
  }
  
  void				freeInstance(T* instance) {
    _poolMap[instance->getType()]->freeInstance(&instance);
  }
};

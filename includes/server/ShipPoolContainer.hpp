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
  std::array<unsigned char, 255>		*_idAvailable;

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

  void				setIdAvailable(std::array<unsigned char, 255> &idAvailable)
  {
	  this->_idAvailable = &idAvailable;
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

  T*				getInstance(entityType type)
  {
	  bool					end = false;
	  Entity				*instance = *(_poolMap[type]->getInstance());
	  for (int i = 1; !end && i < 255; ++i)
	  {
		 if ((*this->_idAvailable)[i])
		  {
			 end = true;
			  instance->setID(i);
			  (*this->_idAvailable)[i] = false;
		 }
	  }
    return (instance);
  }
  
  void				freeInstance(T* instance) {
	  bool					end = false;

	  (*this->_idAvailable)[instance->getID()] = true;
	 _poolMap[instance->getType()]->freeInstance(&instance);
  }
};

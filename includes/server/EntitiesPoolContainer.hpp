#pragma once

# include			<map>

# include			"Pool.hpp"
# include			"Entities.h"

# include			"ShotSmall.h"
# include			"ShotMedium.h"
# include			"ShotBig.h"
# include			"ShotBiggest.h"
# include			"ShotEnemy.h"

template <typename T = Entity>
class				EntitiesPoolContainer
{
private:
  std::map<entityType, GenericIPool *>	_poolMap;
  std::map<entityType, unsigned int>	_poolSizeMap;

public:
  EntitiesPoolContainer() {}

  ~EntitiesPoolContainer() {}

  template <typename U, unsigned int SIZE>
  bool				addPool(entityType type)
  {
    if (_poolMap[type])
      return false;
    _poolMap[type] = new Pool<U, SIZE>;
    return true;
  }

  template <typename U>
  T*				getInstance(entityType type) {
    return (dynamic_cast<IPool<U>* >(_poolMap[type]))->getInstance();
  }
  
  template <typename U>
  void				freeInstance(T* instance) {
    dynamic_cast<IPool<U>* >(_poolMap[instance->getType()])->freeInstance();
  }
};

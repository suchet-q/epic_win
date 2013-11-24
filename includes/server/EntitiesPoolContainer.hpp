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
	std::array<unsigned char, 255>		*_idAvailable;
  std::map<entityType, GenericIPool *>	_poolMap;
  std::map<entityType, unsigned int>	_poolSizeMap;

public:
  EntitiesPoolContainer() {}

  ~EntitiesPoolContainer() {}

  void					setIdAvailable(std::array<unsigned char, 255> &idAvailable)
  {
	  this->_idAvailable = idAvailable;
  }

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
	  dynamic_cast<IPool<U>* >(_poolMap[(instance->getType() >= PLAYER1 && instance->getType() <= PLAYER4) ? PLAYERS : instance->getType()])->freeInstance(dynamic_cast<U *>(instance));
  }
};

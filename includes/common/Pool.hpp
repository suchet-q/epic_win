#pragma once

# include			<array>

# include			"IPool.hpp"

template<typename T, unsigned int NB_ELEM>
class				Pool : public IPool<T>
{
private:
  std::array<bool, NB_ELEM>	_idArray;
  std::array<T, NB_ELEM>	_pool;

public:
  Pool() {
    for (unsigned int i = 0; i < NB_ELEM; ++i)
      this->_idArray[i] = false;
  }
 
  ~Pool() {}

  T*				getInstance() {
    unsigned int		i = 0;

    for (; i < NB_ELEM && this->_idArray[i]; ++i);
    this->_idArray[i] = true;
    return &(this->_pool[i]);
  }
  void				freeInstance(T* instance) {
    unsigned int		i = 0;

    for (; i < NB_ELEM && &(this->_pool[i]) != instance; ++i);
      this->_idArray[i] = false;
  }

  std::array<T, NB_ELEM>&	getArray() {
    return this->_pool;
  }

  T*				getElem(unsigned int i) {
    return &(this->_pool[i]);
  }
};

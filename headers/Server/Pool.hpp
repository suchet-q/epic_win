#pragma once

# include			<array>

# define			NB_ELEM		(64)

template<typename T>
class				Pool
{
private:
  std::array<bool, NB_ELEM>	_idArray;
  std::array<T, NB_ELEM>	_pool;

public:
  Pool() {
    for (unsigned int i = 0; i < NB_ELEM; ++i)
      this->_idArray[i] = false;
  }
  ~Pool();

  T*				getInstance() {
    unsigned int		i = 0;

    for (; i < NB_ELEM && this->_idArray[i]; ++i);
    return &(this->_pool[i]);
  }
  void				freeInstance(T* instance) {
    unsigned int		i = 0;

    for (; i < NB_ELEM && this->_pool[i] != *instance; ++i);
      this->_idArray[i] = false;
  }
};

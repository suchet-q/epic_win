#pragma once

# include			<array>

# include			"GenericIPool.h"

template<typename T>
class				IPool : public GenericIPool
{
public:
  IPool() {}
  virtual ~IPool() {}

  virtual T*			getInstance() = 0;
  virtual void			freeInstance(T* instance) = 0;

  virtual T*			getElem(unsigned int i) = 0;
};

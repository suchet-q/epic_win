#pragma once

# include			<array>

# include			"IPool.h"

template<typename T>
class				APool : public IPool
{
public:
  APool() {}
  virtual ~APool() {}

  virtual T*			getInstance() = 0;
  virtual void			freeInstance(T* instance) = 0;
};

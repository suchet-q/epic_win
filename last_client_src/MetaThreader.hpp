//
// MetaThreader.hpp for MetaThreader.hpp in /home/suchet_q//tek3/rtype/thread
// 
// Made by quentin suchet
// Login   <suchet_q@epitech.net>
// 
// Started on  Tue Oct 22 09:38:33 2013 quentin suchet
// Last update Tue Oct 22 09:52:08 2013 quentin suchet
//

#pragma once

#ifdef _WIN32
# include "ThreaderWindows.hpp"
#else
# include "ThreaderLinux.hpp"
#endif

template<typename I, typename V, typename T = 
#ifdef _WIN32
	 ThreaderWindows<I, V>
#else
	 ThreaderLinux<I,V>
#endif
	 >
class		MetaThreader
{
  T		_threader;

public:
  MetaThreader() {}
  ~MetaThreader() {}
  
  void		*getPthread() const
  {
    return this->_threader.getPthread();
  }

  bool		start(int (I::*ptr)(V *), I *inst, V *var)
  {
    return this->_threader.start(ptr, inst, var);
  }
  
  int		waitThread()
  {
    return this->_threader.waitThread();
  }

  bool		isAlive()
  {
    return this->_threader.isAlive();
  }

  bool		killThread()
  {
    return this->_threader.killThread();
  }
  
  
  void		exit()
  {
    this->_threader.exit();
  }
};

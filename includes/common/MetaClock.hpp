#pragma once

#ifdef	_WIN32
# include "windows/ClockWindows.h"
#else
# include "linux/ClockLinux.h"
#endif


template<class T = 
#ifdef	_WIN32
	ClockWindows
#else
	ClockLinux
#endif
	 >
class		MetaClock
{
  T		_clock;

public:
  MetaClock() {}
  ~MetaClock() {}
  
  void		start()
  {
    this->_clock.start();
  }

  unsigned long int	elapsedTime()
  {
    return this->_clock.elapsedTime();
  }

  unsigned long int	elapsedTimeSinceStart()
  {
    return this->_clock.elapsedTimeSinceStart();
  }

  void			stop()
  {
    this->_clock.stop();
  }
};

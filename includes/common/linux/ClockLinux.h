#pragma once

#include	<time.h>
#include	<sys/time.h>

class		ClockLinux
{
  unsigned long int	_lastUpdate;
  unsigned long int	_fromBeginning;
  struct timeval	_buff;

 public:
  ClockLinux();
  ~ClockLinux();
  void			start();
  unsigned long int	elapsedTime();
  unsigned long int	elapsedTimeSinceStart();
  void			stop();
};

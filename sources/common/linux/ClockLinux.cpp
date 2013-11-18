#include		"ClockLinux.h"

ClockLinux::ClockLinux() : _lastUpdate(0), _fromBeginning(0) {}

ClockLinux::~ClockLinux() {}

void			ClockLinux::start()
{
  unsigned long int	buf;

  gettimeofday(&this->_buff, NULL);
  buf = (this->_buff.tv_sec * 1000000) + this->_buff.tv_usec;
  this->_lastUpdate = buf;
  this->_fromBeginning = buf;
}

unsigned long int	ClockLinux::elapsedTime()
{
  unsigned long int	buf;
  unsigned long int	res;

  gettimeofday(&this->_buff, NULL);
  buf = (this->_buff.tv_sec * 1000000) + (this->_buff.tv_usec);
  res = buf - this->_lastUpdate;
  this->_lastUpdate = buf;
  return (res);
}

unsigned long int	ClockLinux::elapsedTimeSinceStart()
{
  unsigned long int	buf;
  unsigned long int	res;

  gettimeofday(&this->_buff, NULL);
  buf = (this->_buff.tv_sec * 1000000) + this->_buff.tv_usec;
  res = buf - this->_fromBeginning;
  return (res);
}

void			ClockLinux::stop()
{
  this->_lastUpdate = 0;
  this->_fromBeginning = 0;
}

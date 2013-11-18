#include	"Windows/ClockWindows.h"

ClockWindows::ClockWindows() : _lastUpdate(0), _fromBeginning(0) {}

ClockWindows::~ClockWindows() {}

void			ClockWindows::start()
{
	unsigned long int	buf;

	gettimeofday(&this->_buff);
	buf = (this->_buff.tv_sec * 1000000) + this->_buff.tv_usec;
	this->_lastUpdate = buf;
	this->_fromBeginning = buf;
}

unsigned long int	ClockWindows::elapsedTime()
{
	unsigned long int	buf;
	unsigned long int	res;

	gettimeofday(&this->_buff);
	buf = (this->_buff.tv_sec * 1000000) + (this->_buff.tv_usec);
	res = buf - this->_lastUpdate;
	this->_lastUpdate = buf;
	return (res);
}

unsigned long int	ClockWindows::elapsedTimeSinceStart()
{
	unsigned long int	buf;
	unsigned long int	res;

	gettimeofday(&this->_buff);
	buf = (this->_buff.tv_sec * 1000000) + this->_buff.tv_usec;
	res = buf - this->_fromBeginning;
	return (res);
}

void			ClockWindows::stop()
{
	this->_lastUpdate = 0;
	this->_fromBeginning = 0;
}

int			ClockWindows::gettimeofday(struct timeval *tv) const
{
	FILETIME ft;
	unsigned __int64 tmpres = 0;
	static int tzflag;

	if (NULL != tv)
	{
		GetSystemTimeAsFileTime(&ft);
		tmpres |= ft.dwHighDateTime;
		tmpres <<= 32;
		tmpres |= ft.dwLowDateTime;
		/*converting file time to unix epoch*/
		tmpres -= DELTA_EPOCH_IN_MICROSECS;
		tmpres /= 10;  /*convert into microseconds*/
		tv->tv_sec = (long)(tmpres / 1000000UL);
		tv->tv_usec = (long)(tmpres % 1000000UL);
	}
	return 0;
}
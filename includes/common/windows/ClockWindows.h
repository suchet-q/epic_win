#pragma once
#include <time.h>
#include "WindowsInclude.h"//I've ommited this line.
#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

class		ClockWindows
{
	unsigned long int	_lastUpdate;
	unsigned long int	_fromBeginning;
	struct timeval		_buff;

	int					gettimeofday(struct timeval *tv) const;
public:
	ClockWindows();
	~ClockWindows();
	void				start();
	unsigned long int	elapsedTime();
	unsigned long int	elapsedTimeSinceStart();
	void				stop();
};
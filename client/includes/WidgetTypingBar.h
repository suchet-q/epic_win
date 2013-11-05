#pragma once
#include	"WidgetText.h"

class WidgetTypingBar : public WidgetText
{
	bool			_activated;
	float			_timer;
public:
	WidgetTypingBar(void);
	~WidgetTypingBar(void);

	void			update(float, RenderWindow &, int);
	void			switchActivate();
	void			desactivate();
};


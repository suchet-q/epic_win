#pragma once
#include	"RenderWindow.h"
#include	"WidgetImage.h"
#include	"ManageWindow.h"

class GameLoop
{
	WidgetImage	_back1;
	WidgetImage	_back2;

	void		drawHUB(RenderWindow &, float);
	void		drawEntities(RenderWindow &, float);
	void		drawBackground(RenderWindow &, float);
public:
	GameLoop(void);
	~GameLoop(void);

	bool		loop(RenderWindow &);
	int			loadResources(void *);
};


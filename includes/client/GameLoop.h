#pragma once

#include	<sstream>
#include	"RenderWindow.h"
#include	"WidgetImage.h"
#include	"WidgetText.h"
#include	"ManageWindow.h"
#include	"Parser.h"
#include	"GameSocket.h"
#include	"RuntimeException.h"

class GameLoop
{
	WidgetImage			_back1;
	WidgetImage			_back2;
	WidgetText			_life;
	WidgetText			_score;
	int					_scoreNb;
	int					_lifeNb;
	unsigned char *		_idClient;
	RuntimeException	_exception;
	bool				_exceptionOccured;

	void		drawHUB(RenderWindow &, float);
	void		drawEntities(RenderWindow &, float);
	void		drawBackground(RenderWindow &, float);
	void		handleInputs(sf::Input &, Parser &);
public:
	GameLoop(void);
	~GameLoop(void);

	boost::any	aff(std::list<boost::any> &);
	void		exception();
	bool		loop(RenderWindow &, Parser &, GameSocket &);
	int			loadResources(void *);
};


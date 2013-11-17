#pragma once

#include	<sstream>
#include	"RenderWindow.h"
#include	"WidgetImage.h"
#include	"WidgetText.h"
#include	"ManageWindow.h"
#include	"Parser.h"
#include	"GameSocket.h"
#include	"RuntimeException.h"
#include	"ManageWindow.h"

class GameLoop
{
	WidgetImage			_back1;
	WidgetImage			_back2;
	WidgetText			_life;
	WidgetText			_score;
	WidgetText			_fps;
	int					_scoreNb;
	int					_lifeNb;
	unsigned char *		_idClient;
	RuntimeException	_exception;
	bool				_exceptionOccured;
	Managewindow		*_manager;
	float				_vsyncFactor;
	float				_vsyncDelay;

	void		drawHUB(RenderWindow &, float);
	void		drawEntities(RenderWindow &, float);
	void		drawBackground(RenderWindow &, float);
	void		handleInputs(sf::Input &, Parser &);
public:
	GameLoop(void);
	~GameLoop(void);

	boost::any	aff(std::list<boost::any> &);
	boost::any	life(std::list<boost::any> &);
	boost::any	score(std::list<boost::any> &);
	void		exception();
	bool		loop(RenderWindow &, Parser &, GameSocket &);
	int			loadResources(void *);
	void		handleInputs(const sf::Input &, Parser &);
};


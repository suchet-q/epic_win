#pragma once
#include	<iostream>
#include	"AWidget.h"

class WidgetImage : public AWidget
{
	float			_resetDelay;
	float			_resetTransition;
public:
	WidgetImage(void);
	~WidgetImage(void);

	virtual void	loadSprites(std::list<std::pair<sf::Vector2i, sf::Vector2i> > &);
	virtual void	loadSprites(std::list<std::pair<sf::Vector2i, sf::Vector2i> > &, unsigned char r, unsigned char g, unsigned char b);
	virtual void	setPosition(std::list<sf::Vector2f> &);
	virtual void	setAnimations(std::list<std::pair<sf::Vector2f, float> > &);
	virtual void	update(float, RenderWindow &, int);
	virtual void	resetWidget();
	virtual void	setResetParameters(float, float);
};

#pragma once
#include	"AWidget.h"

class WidgetLogo : public AWidget
{
public:
	WidgetLogo(void);
	~WidgetLogo(void);

	virtual void	loadSprites(std::list<std::pair<sf::Vector2f, sf::Vector2f>> &);
	virtual void	setPosition(std::list<sf::Vector2f> &);
	virtual void	setAnimations(std::list<std::pair<sf::Vector2f, float>> &);
	virtual void	update(float, RenderWindow &);
};


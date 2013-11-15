#pragma once
#include	<map>
#include	"AWidget.h"
#include	"SoundPool.h"

class WidgetButton : public AWidget
{
protected:
	bool			_hovered;
	float			_resetDelay;
	int				_destinationSheet;
	bool			_clickable;
	bool			_animationFinished;
	bool			_clickPushed;
	Sheets*			_sheet;
public:
	WidgetButton(void);
	virtual ~WidgetButton(void);

	virtual void	loadSprites(std::list<std::pair<sf::Vector2f, sf::Vector2f> > &);
	virtual void	setPosition(std::list<sf::Vector2f> &);
	virtual void	setAnimations(std::list<std::pair<sf::Vector2f, float> > &);
	virtual void	update(float, RenderWindow &, int);
	virtual void	setHover();
	virtual void	setUnhover();
	virtual void	handleInputs(RenderWindow &);
	virtual void	setDestinationSheet(int);
	virtual void	loadDestinationSheet();
	virtual void	setClickable();
	virtual void	setUnclickable();
	virtual void	setResetParameters(float);
	virtual void	resetWidget();
	void			setSheet(Sheets *);
};


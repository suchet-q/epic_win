#pragma once
#include	"WidgetButton.h"

class WidgetSwitch : public WidgetButton
{
	std::list<int>	_originalSheets;
	bool			_visible;
public:
	WidgetSwitch(void);
	virtual ~WidgetSwitch(void);

	void		setVisible();
	void		setUnvisible();
	void		cancelAnimations();
	virtual void	setClickable();
	virtual void	setUnclickable();
	virtual void	resetWidget();
	void			clearSheets();
	bool			isSelected();
};


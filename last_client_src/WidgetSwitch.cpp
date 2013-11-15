#include "WidgetSwitch.h"


WidgetSwitch::WidgetSwitch(void) : WidgetButton()
{
	this->_visible = true;
}

WidgetSwitch::~WidgetSwitch(void)
{
}

void		WidgetSwitch::setVisible()
{
	if (!(this->_visible))
	{
		this->_actualSheets = this->_originalSheets;
		this->_visible = true;
	}
}

void		WidgetSwitch::setUnvisible()
{
	if (this->_visible)
	{
		this->_originalSheets = this->_actualSheets;
		this->_actualSheets.clear();
		this->_actualSheets.push_back(-1);
		this->_visible = false;
	}
}

void		WidgetSwitch::clearSheets()
{
	this->_actualSheets.clear();
	this->_originalSheets.clear();
}

void		WidgetSwitch::setClickable()
{
	this->_clickable = true;
}

bool		WidgetSwitch::isSelected()
{
	if (this->_visible)
		return (true);
	return (false);
}

void		WidgetSwitch::setUnclickable()
{
	this->_clickable = false;
}

void		WidgetSwitch::cancelAnimations()
{
	bool	finished = false;

	while (!finished)
	{
		finished = true;
		for (int i = 0; i < this->_sprites.size(); ++i)
			if (this->_sprites[i]->updateAnimation(1337.0))
				finished = false;
	}
	this->setDelay(0.0);
}

void		WidgetSwitch::resetWidget()
{
	this->_hovered = false;
	for (int i = 0; i < this->_sprites.size(); ++i)
	{
		this->_sprites[i]->resetPosition();
		this->_sprites[i]->loadAnimationsBackup();
	}	
	this->setDelay(this->_resetDelay);
}
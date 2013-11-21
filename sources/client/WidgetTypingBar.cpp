#include "WidgetTypingBar.h"


WidgetTypingBar::WidgetTypingBar(void) : WidgetText()
{
	this->setStyle(sf::Text::Bold, 30, "Images/charlie_dotted.ttf", 255, 255, 255);
	this->_text.setString("| ");
	this->_activated = false;
	this->_timer = 0.6f;
}


WidgetTypingBar::~WidgetTypingBar(void)
{
}

void		WidgetTypingBar::update(float elapsed, RenderWindow &win, int size)
{
	if (!this->_activated)
		return;
	if (this->_useDelay && this->_delay > 0.0)
	{
		this->_delay -= elapsed;
		return;
	}
	if ((this->_timer -= elapsed) > 0.0)
	{
		this->_text.setCharacterSize(static_cast<float>(size));
		win.drawText(this->_text);
	}
	else if (this->_timer <= -0.6f)
		this->_timer = 0.6f;
}

void		WidgetTypingBar::switchActivate()
{
	this->_activated = !(this->_activated);
}

void		WidgetTypingBar::desactivate()
{
	this->_activated = false;
}
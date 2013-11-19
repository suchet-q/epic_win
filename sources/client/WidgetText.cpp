#include "WidgetText.h"

sf::Mutex	WidgetText::_mutex;

WidgetText::WidgetText(void) : AWidget()
{
	this->_resetDelay = 0.0;
}


WidgetText::~WidgetText(void)
{
}


void		WidgetText::loadSprites(std::list<std::pair<sf::Vector2i, sf::Vector2i> > &subRects)
{

}

void		WidgetText::setPosition(std::list<sf::Vector2f> &pos)
{
	this->_text.SetPosition(pos.front());
}

void		WidgetText::setPosition(sf::Vector2f pos)
{
	this->_text.SetPosition(pos);
}

void		WidgetText::setAnimations(std::list<std::pair<sf::Vector2f, float> > &anims)
{

}

void		WidgetText::update(float elapsed, RenderWindow &win, int sheetNb)
{
	bool	found = false;
	std::list<int>::iterator	it;

	for (it = this->_actualSheets.begin(); it != this->_actualSheets.end(); ++it)
		if ((*it) == sheetNb)
			found = true;
	if (!found)
		return;
	if (this->_useDelay && this->_delay > 0.0)
	{
		this->_delay -= elapsed;
		return;
	}
	if (this->_useTimeToLive && (this->_timeToLive -= elapsed) <= 0.0)
		return;
	win.drawText(this->_text);
}

void		WidgetText::setCenter(int x, int y)
{
	this->_text.SetCenter(static_cast<float>(x), static_cast<float>(y));
}

void		WidgetText::setText(const std::string &text)
{
	this->_text.SetText(text);
}

void		WidgetText::setStyle(unsigned long style, int size, std::string const &font,
				     unsigned char r, unsigned char g, unsigned char b)
{
	this->_text.SetStyle(style);
	this->_text.SetSize(static_cast<float>(size));
	if (font != "")
	{
	  this->_mutex.Lock();
	  this->_font.LoadFromFile(font);
	  this->_text.SetFont(this->_font);
	  this->_mutex.Unlock();
	}
	this->_text.SetColor(sf::Color(r, g, b));
}

boost::any		WidgetText::refreshText(std::list<boost::any> args)
{
	std::string	text = boost::any_cast<std::string>(args.front());

	this->_text.SetText(text);
	return (0);
}

void		WidgetText::setResetParameters(float delay)
{
	this->_resetDelay = delay;
}

void		WidgetText::resetWidget()
{
	this->setDelay(this->_resetDelay);
}

sf::FloatRect	WidgetText::getRect()
{
	return (this->_text.GetRect());
}

int				WidgetText::getSize()
{
	return (static_cast<int>(this->_text.GetSize()));
}

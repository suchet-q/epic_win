#include "WidgetImage.h"


WidgetImage::WidgetImage(void) : AWidget()
{
	this->_resetDelay = 0.0;
	this->_resetTransition = 0.0;
}


WidgetImage::~WidgetImage(void)
{
}

void		WidgetImage::loadSprites(std::list<std::pair<sf::Vector2f, sf::Vector2f> > &subRects)
{
	std::list<std::pair<sf::Vector2f, sf::Vector2f> >::iterator	it;
	Sprite	*sprite = new Sprite;
	Sprite	*original = sprite;

	sprite->loadFromFile(this->_img, true, 0, 0, 0);
	for (it = subRects.begin(); it != subRects.end(); ++it)
	{
		sprite->setImage(original->getImage());
		sprite->setMask(0, 0, 0);
		sprite->cut((*it).first, (*it).second);
		this->_sprites.push_back(sprite);
		if ((*it) != subRects.back())
			sprite = new Sprite;
	}
}

void		WidgetImage::loadSprites(std::list<std::pair<sf::Vector2f, sf::Vector2f> > &subRects, unsigned char r, unsigned char g, unsigned char b)
{
	std::list<std::pair<sf::Vector2f, sf::Vector2f> >::iterator	it;
	Sprite	*sprite = new Sprite;
	Sprite	*original = sprite;

	sprite->loadFromFile(this->_img, true, r, g, b);
	
	for (it = subRects.begin(); it != subRects.end(); ++it)
	{
		sprite->setImage(original->getImage());
		sprite->setMask(r, g, b);
		sprite->cut((*it).first, (*it).second);
		this->_sprites.push_back(sprite);
		if ((*it) != subRects.back())
			sprite = new Sprite;
	}
}

void		WidgetImage::setPosition(std::list<sf::Vector2f> &pos)
{
	std::list<sf::Vector2f>::iterator	it;
	int									i = 0;

	for (it = pos.begin(); it != pos.end(); ++it)
	{
		this->_sprites[i]->place(SP_POS, (*it), sf::Vector2f(0, 0), sf::Vector2f(0, 0), 0);
		++i;
	}
}

void		WidgetImage::setAnimations(std::list<std::pair<sf::Vector2f, float> > &anims)
{
	std::list<std::pair<sf::Vector2f, float> >::iterator	it;
	int													i = 0;

	for (it = anims.begin(); it != anims.end(); ++it)
	{
		this->_sprites[i]->queueAnimation((*it).first, (*it).second);
		++i;
	}
}

void		WidgetImage::update(float elapsed, RenderWindow &win, int sheetNb)
{
	bool	finished, found = false;
	unsigned char	alpha = 255;
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
	for (int i = 0; i < this->_sprites.size(); ++i)
	{
		if (this->_useTransition && this->_transition >= 0.0)
		{
			if ((this->_transition -= elapsed) >= 1.0)
				alpha = 255 * (1.0 - (this->_transition - 1.0));
			else if (this->_transitionFull)
				alpha = 255 * ((this->_transition < 0.5) ? (0.5) : (this->_transition));
			this->_sprites[i]->setAlpha(alpha);
		}
		if (this->_sprites[i]->updateAnimation(elapsed))
			finished = false;
		this->_sprites[i]->draw(win);
	}
}

void		WidgetImage::setResetParameters(float delay, float transition)
{
	this->_resetDelay = delay;
	this->_resetTransition = transition;
}

void		WidgetImage::resetWidget()
{
	for (int i = 0; i < this->_sprites.size(); ++i)
	{
		this->_sprites[i]->resetPosition();
		this->_sprites[i]->loadAnimationsBackup();
	}
	this->setDelay(this->_resetDelay);
	this->setTransitionTime(this->_resetTransition, false);
}


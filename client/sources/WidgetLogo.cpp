#include "WidgetLogo.h"


WidgetLogo::WidgetLogo(void)
{
}


WidgetLogo::~WidgetLogo(void)
{
}


void		WidgetLogo::loadSprites(std::list<std::pair<sf::Vector2f, sf::Vector2f>> &subRects)
{
	std::list<std::pair<sf::Vector2f, sf::Vector2f>>::iterator	it;
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

void		WidgetLogo::setPosition(std::list<sf::Vector2f> &pos)
{
	std::list<sf::Vector2f>::iterator	it;
	int									i = 0;

	for (it = pos.begin(); it != pos.end(); ++it)
	{
		this->_sprites[i]->place(SP_POS, (*it), sf::Vector2f(0, 0), sf::Vector2f(0, 0), 0);
		++i;
	}
}

void		WidgetLogo::setAnimations(std::list<std::pair<sf::Vector2f, float>> &anims)
{
	std::list<std::pair<sf::Vector2f, float>>::iterator	it;
	int													i = 0;

	for (it = anims.begin(); it != anims.end(); ++it)
	{
		this->_sprites[i]->queueAnimation((*it).first, (*it).second);
		++i;
	}
}

void		WidgetLogo::update(float elapsed, RenderWindow &win)
{
	int		i = 0;
	bool	finished;

	for (i = 0; i < this->_sprites.size(); ++i)
	{
		if (this->_sprites[i]->updateAnimation(elapsed))
			finished = false;
		this->_sprites[i]->draw(win);
	}
}
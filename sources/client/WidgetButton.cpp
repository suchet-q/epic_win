#include "WidgetButton.h"


WidgetButton::WidgetButton(void) : AWidget()
{
	this->_resetDelay = 0.0;
	this->_clickable = true;
	this->_hovered = false;
	this->_clickPushed = false;
	this->_animationFinished = false;
	this->setCallback("hover", this, &WidgetButton::setHover);
	this->setCallback("hover", SoundPool::getInstance(), &SoundPool::buttonHover);
	this->setCallback("unhover", this, &WidgetButton::setUnhover);
	this->setCallback("click", SoundPool::getInstance(), &SoundPool::buttonClicked);
}

WidgetButton::~WidgetButton(void)
{
}

void		WidgetButton::loadSprites(std::list<std::pair<sf::Vector2i, sf::Vector2i> > &subRects)
{
	std::list<std::pair<sf::Vector2i, sf::Vector2i> >::iterator	it;
	Sprite	*sprite = new Sprite;
	Sprite	*original = sprite;

	sprite->loadFromFile(this->_img);
	
	for (it = subRects.begin(); it != subRects.end(); ++it)
	{
		sprite->setTexture(original->getTexture());
		sprite->cut((*it).first, (*it).second);
		this->_sprites.push_back(sprite);
		if ((*it) != subRects.back())
			sprite = new Sprite;
	}
}

void		WidgetButton::setPosition(std::list<sf::Vector2f> &pos)
{
	std::list<sf::Vector2f>::iterator	it;
	int									i = 0;

	for (it = pos.begin(); it != pos.end(); ++it)
	{
		this->_sprites[i]->place(SP_POS, (*it), sf::Vector2f(0, 0), sf::Vector2f(0, 0), 0);
		++i;
	}
}

void		WidgetButton::setAnimations(std::list<std::pair<sf::Vector2f, float> > &anims)
{
	std::list<std::pair<sf::Vector2f, float> >::iterator	it;
	int													i = 0;

	for (it = anims.begin(); it != anims.end(); ++it)
	{
		this->_sprites[i]->queueAnimation((*it).first, (*it).second);
	}
}

void		WidgetButton::handleInputs(RenderWindow &win)
{
	sf::Vector2f	position;
	sf::FloatRect	size;

	(this->_hovered) ? (position = this->_sprites[1]->getPosition()) : (position = this->_sprites[0]->getPosition());
	size = this->_sprites[0]->getSize();
	/*if (input.GetMouseX() >= position.x && input.GetMouseX() <= (position.x + size.x) &&
		input.GetMouseY() >= position.y && input.GetMouseY() <= (position.y + size.y))
	{
		if (!(this->_hovered))
		{
			this->_hovered = true;
			this->triggerCallback("hover");
		}
		if (input.IsMouseButtonDown(sf::Mouse::Left))
			this->_clickPushed = true;
		else if (this->_clickPushed)
		{
			this->_clickPushed = false;
			this->triggerCallback("click");
		}
	}
	else if (this->_hovered)
	{
		this->_hovered = false;
		this->triggerCallback("unhover");
	}*/
}

void		WidgetButton::update(float elapsed, RenderWindow &win, int sheetNb)
{
	bool	finished = true, found = false;
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
	if (this->_clickable)
		this->handleInputs(win);
	for (unsigned int i = 0; i < this->_sprites.size(); ++i)
	{
		if (this->_sprites[i]->updateAnimation(elapsed))
			finished = false;
		this->_sprites[i]->draw(win);
	}
	if (this->_animationFinished == false && finished)
		this->triggerCallback("animationFinished");
	this->_animationFinished = finished;
}

void		WidgetButton::setHover()
{
	std::list<sf::Vector2f>		pos;

	pos.push_back(sf::Vector2f(WIN_X, WIN_Y));
	pos.push_back(this->_sprites[0]->getPosition());
	this->setPosition(pos);
}

void		WidgetButton::setUnhover()
{
	std::list<sf::Vector2f>		pos;

	pos.push_back(this->_sprites[1]->getPosition());
	pos.push_back(sf::Vector2f(WIN_X, WIN_Y));
	this->setPosition(pos);
}

void		WidgetButton::setDestinationSheet(int sheet)
{
	this->_destinationSheet = sheet;
}

void		WidgetButton::loadDestinationSheet()
{
	this->_sheet->setActualSheet(this->_destinationSheet);
}

void		WidgetButton::setClickable()
{
	this->_clickable = true;
}

void		WidgetButton::setSheet(Sheets *sheet)
{
	this->_sheet = sheet;
}

void		WidgetButton::setUnclickable()
{
	this->_clickable = false;
}

void		WidgetButton::setResetParameters(float delay)
{
	this->_resetDelay = delay;
}

void		WidgetButton::resetWidget()
{
	this->_hovered = false;
	for (int unsigned i = 0; i < this->_sprites.size(); ++i)
	{
		this->_sprites[i]->resetPosition();
		this->_sprites[i]->loadAnimationsBackup();
	}	
	this->setDelay(this->_resetDelay);
}

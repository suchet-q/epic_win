#include "Sprite.h"


Sprite::Sprite(void)
{
	this->_initialPos.x = -1337;
	this->_initialPos.y = -1337;
}


Sprite::~Sprite(void)
{
}

Sprite::Sprite(const Sprite &sprite)
{
	this->_sprite.SetImage(const_cast<Sprite &>(sprite).getImage());
}

void		Sprite::setImage(sf::Image &img)
{
	this->_sprite.SetImage(img);
}

sf::Image&	Sprite::getImage()
{
	return (this->_img);
}

void		Sprite::setMask(unsigned char r, unsigned char g , unsigned char b)
{
	this->_img.CreateMaskFromColor(sf::Color(r, g, b));
}

bool		Sprite::loadFromFile(std::string const & filename, bool useMask, unsigned char r, unsigned char g , unsigned char b)
{
	if (!(this->_img.LoadFromFile(filename)))
		return (false);
	if (useMask)
		this->_img.CreateMaskFromColor(sf::Color(r, g, b));
	this->_sprite.SetImage(this->_img);
	return (true);
}

void		Sprite::draw(RenderWindow &window)
{
	window.drawSprite(this->_sprite);
}

void		Sprite::place(unsigned char flags, sf::Vector2f position, sf::Vector2f translate, sf::Vector2f scale, float angle)
{
	if ((flags & SP_TRS) == SP_TRS)
		this->_sprite.Move(translate);
	if ((flags & SP_SCL) == SP_SCL)
		this->_sprite.Scale(scale);
	if ((flags & SP_ROT) == SP_ROT)
		this->_sprite.Rotate(angle);
	if ((flags & SP_POS) == SP_POS)
	{
		this->_sprite.SetPosition(position);
		this->_floatPos.x = position.x;
		this->_floatPos.y = position.y;
		if (this->_initialPos.x == -1337 && this->_initialPos.y == -1337)
			this->_initialPos = position;
	}
}

void		Sprite::resetPosition()
{
	this->_sprite.SetPosition(this->_initialPos);
	this->_floatPos.x = this->_initialPos.x;
	this->_floatPos.y = this->_initialPos.y;
}

void		Sprite::setAlpha(unsigned char level)
{
	this->_sprite.SetColor(sf::Color(255, 255, 255, level));
}

sf::Vector2f	Sprite::getSize()
{
	return (this->_sprite.GetSize());
}

sf::Vector2f	Sprite::getPosition()
{
	return (this->_sprite.GetPosition());
}

void			Sprite::cut(sf::Vector2f begin, sf::Vector2f end)
{
	this->_sprite.SetSubRect(sf::IntRect(begin.x, begin.y, end.x, end.y));
}

void			Sprite::queueAnimation(sf::Vector2f destination, float time)
{
	this->_animations.push_back(std::pair<sf::Vector2f, float>(destination, time));
	this->_animationsBackup.push_back(std::pair<sf::Vector2f, float>(destination, time));
}

void			Sprite::clearAnimationsBackup()
{
	this->_animationsBackup.clear();
}

void			Sprite::loadAnimationsBackup()
{
	this->_animations = this->_animationsBackup;
}

bool			Sprite::updateAnimation(float elapsed)
{
	int			x, y;

	if (!(this->_animations.empty()))
	{
		if ((this->_animations.front().second -= elapsed) <= 0.0)
		{
			this->place(SP_POS, sf::Vector2f(this->_animations.front().first.x, this->_animations.front().first.y), sf::Vector2f(0, 0), sf::Vector2f(0, 0), 0);
			this->_floatPos.x = this->_animations.front().first.x;
			this->_floatPos.y = this->_animations.front().first.y;
			this->_animations.pop_front();
		}
		else
		{
			x =  this->_animations.front().first.x - this->_floatPos.x;
			y =  this->_animations.front().first.y - this->_floatPos.y;
			this->_floatPos.x += (x / this->_animations.front().second) * elapsed;
			this->_floatPos.y += (y / this->_animations.front().second) * elapsed;
			this->place(SP_POS, this->_floatPos, sf::Vector2f(0, 0), sf::Vector2f(0, 0), 0);
		}
		return (true);
	}
	return (false);
}
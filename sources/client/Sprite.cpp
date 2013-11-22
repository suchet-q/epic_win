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
	this->_img.loadFromImage(const_cast<Sprite &>(sprite).getTexture());
	this->_sprite.setTexture(this->_img);
}

void		Sprite::setTexture(sf::Image &img)
{
	this->_img.loadFromImage(img);
	this->_sprite.setTexture(this->_img);
}

sf::Image&	Sprite::getTexture()
{
	return (this->_image);
}

bool		Sprite::loadFromFile(std::string const & filename)
{
	if (!(this->_image.loadFromFile(filename)))
	{
		throw RuntimeException("[Sprite::loadFromFile]", "Can't load " + filename);
		return (false);
	}
	this->_image.createMaskFromColor(sf::Color(0, 255, 0));
	this->_img.loadFromImage(this->_image);
	this->_sprite.setTexture(this->_img);
	return (true);
}

void		Sprite::draw(RenderWindow &window)
{
	window.drawSprite(this->_sprite);
}

void		Sprite::place(unsigned char flags, sf::Vector2f position, sf::Vector2f translate, sf::Vector2f scale, float angle)
{
	if ((flags & SP_TRS) == SP_TRS)
		this->_sprite.move(translate);
	if ((flags & SP_SCL) == SP_SCL)
		this->_sprite.scale(scale);
	if ((flags & SP_ROT) == SP_ROT)
		this->_sprite.rotate(angle);
	if ((flags & SP_POS) == SP_POS)
	{
		this->_sprite.setPosition(position);
		this->_floatPos.x = position.x;
		this->_floatPos.y = position.y;
		if (this->_initialPos.x == -1337 && this->_initialPos.y == -1337)
			this->_initialPos = position;
	}
}

void		Sprite::resetPosition()
{
	this->_sprite.setPosition(this->_initialPos);
	this->_floatPos.x = this->_initialPos.x;
	this->_floatPos.y = this->_initialPos.y;
}

void		Sprite::setAlpha(unsigned char level)
{
	this->_sprite.setColor(sf::Color(255, 255, 255, level));
}

sf::FloatRect	Sprite::getSize()
{
	return (this->_sprite.getGlobalBounds());
}

sf::Vector2f	Sprite::getPosition()
{
	return (this->_sprite.getPosition());
}

void			Sprite::cut(sf::Vector2i begin, sf::Vector2i end)
{
	this->_sprite.setTextureRect(sf::IntRect(begin.x, begin.y, end.x - begin.x, end.y - begin.y));
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
	float		tmp;

	if (!(this->_animations.empty()))
	{
		tmp = (elapsed - this->_animations.front().second);
		if ((this->_animations.front().second -= elapsed) <= 0.0)
		{
			this->place(SP_POS, sf::Vector2f(this->_animations.front().first.x, this->_animations.front().first.y), sf::Vector2f(0, 0), sf::Vector2f(0, 0), 0);
			this->_floatPos.x = this->_animations.front().first.x;
			this->_floatPos.y = this->_animations.front().first.y;
			
			this->_animations.pop_front();
			if (!(this->_animations.empty()))
				this->updateAnimation(tmp);
		}
		else
		{
			x =  static_cast<int>(this->_animations.front().first.x - this->_floatPos.x);
			y =  static_cast<int>(this->_animations.front().first.y - this->_floatPos.y);
			this->_floatPos.x += (x / this->_animations.front().second) * elapsed;
			this->_floatPos.y += (y / this->_animations.front().second) * elapsed;
			this->place(SP_POS, this->_floatPos, sf::Vector2f(0, 0), sf::Vector2f(0, 0), 0);
		}
		return (true);
	}
	return (false);
}
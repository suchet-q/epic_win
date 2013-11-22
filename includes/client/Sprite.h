#pragma once

#include	<string>
#include	<list>
#include	<SFML/Graphics.hpp>
#include	"RenderWindow.h"
#include	"macros.h"
#include	"RuntimeException.h"

class Sprite
{
	sf::Texture	_img;
	sf::Image	_image;
	sf::Sprite	_sprite;
	std::list<std::pair<sf::Vector2f, float> >	_animations;
	std::list<std::pair<sf::Vector2f, float> >	_animationsBackup;
	sf::Vector2f	_floatPos;
	sf::Vector2f	_initialPos;
public:
	Sprite(void);
	Sprite(const Sprite &);
	~Sprite(void);

	void			setTexture(sf::Image &);
	bool			loadFromFile(std::string const &);
	void			draw(RenderWindow &);
	void			place(unsigned char, sf::Vector2f, sf::Vector2f, sf::Vector2f, float);
	void			setAlpha(unsigned char);
	sf::Image&	getTexture();
	sf::FloatRect	getSize();
	sf::Vector2f	getPosition();
	void			cut(sf::Vector2i, sf::Vector2i);
	void			queueAnimation(sf::Vector2f , float);
	bool			updateAnimation(float);
	void			clearAnimationsBackup();
	void			loadAnimationsBackup();
	void			resetPosition();
};


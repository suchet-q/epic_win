#pragma once

#include	<string>
#include	<list>
#include	<SFML/Graphics.hpp>
#include	"RenderWindow.h"
#include	"Macros.h"
#include	"RuntimeException.h"

class Sprite
{
	sf::Image	_img;
	sf::Sprite	_sprite;
	std::list<std::pair<sf::Vector2f, float> >	_animations;
	std::list<std::pair<sf::Vector2f, float> >	_animationsBackup;
	sf::Vector2f	_floatPos;
	sf::Vector2f	_initialPos;
public:
	Sprite(void);
	Sprite(const Sprite &);
	~Sprite(void);

	void		setImage(sf::Image &);
	void		setMask(unsigned char , unsigned char , unsigned char);
	bool		loadFromFile(std::string const &, bool = false, unsigned char = -1, unsigned char = -1, unsigned char = -1);
	void		draw(RenderWindow &);
	void		place(unsigned char, sf::Vector2f, sf::Vector2f, sf::Vector2f, float);
	void		setAlpha(unsigned char);
	sf::Image&	getImage();
	sf::Vector2f	getSize();
	sf::Vector2f	getPosition();
	void		cut(sf::Vector2i, sf::Vector2i);
	void		queueAnimation(sf::Vector2f , float);
	bool		updateAnimation(float);
	void		clearAnimationsBackup();
	void		loadAnimationsBackup();
	void		resetPosition();
};


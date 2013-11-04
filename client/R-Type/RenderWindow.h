#pragma once

#include	<string>
#include	<SFML/Window.hpp>
#include	<SFML/Graphics.hpp>
#include	<iostream>
#include	"macros.h"

class RenderWindow
{
	sf::RenderWindow *	_win;
	std::string			_nickname;
	std::string			_msg;
	bool				_getNick;
	bool				_getMsg;
public:
	RenderWindow(void);
	~RenderWindow(void);

	bool		openWindow(int, int, const std::string &);
	bool		isRunning();
	void		closeWindow();
	void		handleEvents();
	void		clearWindow();
	void		refreshWindow();
	void		drawSprite(sf::Sprite &);
	void		drawText(sf::String &);
	const sf::Input&	getInput();
	std::string	getNickname();
	std::string	getMsg();
	void		switchNick();
	void		disableNick();
	void		switchMsg();
	void		disableMsg();
	void		clearMsg();
	bool		msgActive();
};


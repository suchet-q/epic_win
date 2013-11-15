#pragma once

#include	<string>
#include	<SFML/Window.hpp>
#include	<SFML/Graphics.hpp>
#include	<iostream>
#include	"Macros.h"
#include	"RuntimeException.h"

class RenderWindow
{
protected:
	sf::RenderWindow *	_win;
	std::string			_nickname;
	std::string			_msg;
	bool				_getNick;
	bool				_getMsg;
public:
	RenderWindow(void);
	virtual ~RenderWindow(void);

	virtual bool		openWindow(int, int, const std::string &);
	virtual bool		isRunning();
	virtual void		closeWindow();
	virtual void		handleEvents();
	virtual void		clearWindow();
	virtual void		refreshWindow();
	virtual void		drawSprite(sf::Sprite &);
	virtual void		drawText(sf::String &);
	const sf::Input&	getInput();
	std::string	getNickname();
	std::string	getMsg();
	void		switchNick();
	void		disableNick();
	void		switchMsg();
	void		disableMsg();
	void		clearMsg();
	bool		msgActive();
	sf::RenderWindow*	getWindow();
};


#pragma once

#include	<string>
#include	<SFML/Window.hpp>
#include	<SFML/Graphics.hpp>
#include	<iostream>
#include	"macros.h"
#include	"RuntimeException.h"
#include	"Parser.h"

class RenderWindow
{
protected:
	sf::RenderWindow *	_win;
	std::string			_nickname;
	std::string			_msg;
	bool				_getNick;
	bool				_getMsg;
	std::list<sf::Event>	_events;
	sf::Mutex				_mutex;
	const sf::Input*		_lastInput;
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
	virtual void		handleClosing();
	virtual void		lockMutex();
	virtual void		unlockMutex();
	const sf::Input&	getInput();
	std::string	getNickname();
	std::string	getMsg();
	void		switchNick();
	void		disableNick();
	void		switchMsg();
	void		disableMsg();
	void		clearMsg();
	bool		msgActive();
	bool		nickActive();
	sf::RenderWindow*	getWindow();
};


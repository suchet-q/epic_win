#pragma once

#include	<vector>
#include	<list>
#include	<iostream>
#include	<boost/bind.hpp>
#include	<boost/function.hpp>
#include	<sstream>
#include	"Macros.h"
#include	"Sprite.h"
#include	"RenderWindow.h"
#include	"WidgetButton.h"
#include	"WidgetImage.h"
#include	"WidgetSwitch.h"
#include	"WidgetText.h"
#include	"WidgetTypingBar.h"
#include	"SoundPool.h"
#include	"Sheets.h"
#include	"GameSocket.h"
#include	"Parser.h"

class GameMenu
{
	std::list<AWidget *>	_widgets;
	std::list<std::pair<WidgetSwitch *, WidgetSwitch *> >	_lobbiesFrame;
	std::list<WidgetText *>									_lobbiesText;
	std::list<std::pair<unsigned char, unsigned char> >		_lobbiesList;
	std::list<WidgetSwitch *>								_playersFrame;
	std::list<WidgetText *>									_playersText;
	std::list<std::pair<unsigned char, std::string> >		_playersList;
	std::list<WidgetText *>									_msgText;
	std::list<std::pair<unsigned char, std::string> >		_msgList;
	Sheets					_sheets;
	sf::Clock				_clock;
	WidgetText*				_input;
	WidgetText*				_inputMsg;
	WidgetTypingBar*		_typingBar;
	unsigned char			_playerId;
	int						_totalLobbies;
	unsigned char			_lobbyId;
	WidgetText*				_playersLabel;
	WidgetText*				_lobbiesLabel;
	Parser					*_parser;
	RenderWindow			*_win;
	int						_sheetNb;

	void					loadText(RenderWindow *);
	void					loadImages();
	void					loadButtons(RenderWindow *);
	void					loadLobbies(WidgetButton *, RenderWindow *);
public:
	GameMenu(void);
	~GameMenu(void);

	void		sendMsg();
	void		refreshPlayers();
	void		refreshLobbies();
	void		refreshMsg();
	void		loadResources(RenderWindow *, Parser &);
	void		update(RenderWindow &);
	void		rstClock();
	boost::any	setPlayerId(std::list<boost::any>);
	boost::any	setTotalPlayers(std::list<boost::any>);
	boost::any	addLobby(std::list<boost::any>);
	boost::any	joinLobby(std::list<boost::any>);
	boost::any	setLobbyId(std::list<boost::any>);
	boost::any	addPlayer(std::list<boost::any>);
	boost::any	addMsg(std::list<boost::any>);
	boost::any	leaveLobby(std::list<boost::any>);
	void		clearLobbies();
	void		clearPlayers();
	void		joinLobby();
	void		createLobby();
	void		setNickname();
	void		leaveLobby();
	void		askNbPlayers();
};


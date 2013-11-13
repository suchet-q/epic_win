#pragma once

#include	<iostream>
#include	"Macros.h"
#include	"RenderWindow.h"
#include	"GameMenu.h"
#include	"GameSocket.h"
#include	"Parser.h"
#include	"ErrorWindow.h"
#include	"MetaThreader.hpp"
#include	"GameLoop.h"
#include	"ManageWindow.h"

class Client
{
	RenderWindow	_win;
	ErrorWindow		_err;
	GameSocket		_socket;
	Parser			_parser;

	bool		menu();
	void		loading(MetaThreader<GameMenu, RenderWindow> &, GameMenu &);
public:
	Client(void);
	~Client(void);

	bool		launch(std::string const &, int);
};


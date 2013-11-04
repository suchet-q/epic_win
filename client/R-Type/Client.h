#pragma once

#include	<iostream>
#include	"macros.h"
#include	"RenderWindow.h"
#include	"GameMenu.h"
#include	"GameSocket.h"
#include	"Parser.h"

class Client
{
	RenderWindow	_win;
	GameSocket		_socket;
	Parser			_parser;
public:
	Client(void);
	~Client(void);

	bool		launch(std::string const &, int);
};


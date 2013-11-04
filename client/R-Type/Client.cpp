#include "Client.h"


Client::Client(void)
{
}


Client::~Client(void)
{
}

bool		Client::launch(std::string const &ip, int port)
{
	GameMenu	menu;

	if (this->_win.openWindow(WIN_X, WIN_Y, "R-Type") == false)
	{
		std::cerr << "[Client::launch] - Couldn't open render window" << std::endl;
		return (false);
	}
	this->_socket.setValues(ip, port);
	menu.loadResources(&(this->_win), this->_parser);
	this->_socket.connectTCP();
	menu.rstClock();
	while (this->_win.isRunning())
	{
		this->_win.clearWindow();
		menu.update(this->_win);
		this->_win.refreshWindow();
		this->_win.handleEvents();
		this->_socket.update(this->_parser);
	}
	return (true);
}
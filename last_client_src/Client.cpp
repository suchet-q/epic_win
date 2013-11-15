#include "Client.h"


Client::Client(void)
{
}


Client::~Client(void)
{
}

void		Client::loading(MetaThreader<GameMenu, RenderWindow> &threader, GameMenu &menu)
{
	WidgetText	loading;
	std::stringstream	ss;
	sf::Clock			clock;
	float				tmp;

	threader.start(&GameMenu::loadResources, &menu, &(this->_win));
	loading.setStyle(sf::String::Bold, 50, "Images/charlie_dotted.ttf", 0, 255, 0);
	loading.addActualSheet(0);
	loading.setPosition(sf::Vector2f(400, 340));
	clock.Reset();
	while (this->_win.isRunning() && threader.isAlive())
	{
		tmp = clock.GetElapsedTime();
		if (clock.GetElapsedTime() >= 1.2)
			clock.Reset();
		ss.str("");
		ss << "Loading ";
		while ((tmp -= 0.3) >= 0.0)
			ss << ". ";
		loading.setText(ss.str());
		this->_win.clearWindow();
		loading.update(0.15, this->_win, 0);
		this->_win.refreshWindow();
		this->_win.handleEvents();
	}
	threader.waitThread();
}

bool		Client::menu(GameLoop& game, MetaThreader<GameMenu, RenderWindow> &threaderMenu, MetaThreader<GameLoop, void> &threaderGame)
{
	GameMenu	menu;

	menu.initParser(this->_parser);
	this->loading(threaderMenu, menu);
	menu.exception();
	threaderGame.start(&GameLoop::loadResources, &game, &(this->_clientID));
	if (!(this->_socket.connectTCP()))
		throw RuntimeException("[Client::launch]", "Couldn't connect to server");  
	menu.rstClock();
	while (this->_win.isRunning() && !(menu.finished()))
	{
		try {
			this->_win.clearWindow();
			menu.update(this->_win);
			this->_win.refreshWindow();
			this->_win.handleEvents();
			this->_socket.update(this->_parser);
		}
		catch (MinorException &e) {
			this->_err.displayError(e.method(), e.what());
		}
	}
	this->_socket.setUDPPort(menu.getUDPPort());
	this->_clientID = menu.getPlayerID();
	return (true);
}

bool		Client::launch(std::string const &ip, int port)
{
	GameLoop		game;
	MetaThreader<GameMenu, RenderWindow>	threaderMenu;
	MetaThreader<GameLoop, void>			threaderGame;

	try { 
		this->_err.initialize();
	}
	catch (RuntimeException &e) {
		return (false);
	}
	if (this->_win.openWindow(WIN_X, WIN_Y, "R-Type") == false)
	{
		this->_err.displayError("[Client::launch]", "Couldn't open render window");
		return (false);
	}
	try {
		this->_socket.setValues(ip, port);
		this->menu(game, threaderMenu, threaderGame);
		game.exception();
		game.loop(this->_win, this->_parser, this->_socket);
	}
	catch (RuntimeException &e) {
		threaderMenu.killThread();
		threaderGame.killThread();
		this->_err.displayError(e.method(), e.what());
		this->_win.closeWindow();
		return (false);
	}
	
	return (true);
}

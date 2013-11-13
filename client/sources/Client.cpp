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

bool		Client::menu()
{
	GameMenu	menu;
	MetaThreader<GameMenu, RenderWindow>	threader;

	menu.initParser(this->_parser);
	this->loading(threader, menu);
	if (!(this->_socket.connectTCP()))
	  {
		this->_err.displayError("[Client::launch]", "Couldn't connect to server");
		return (false);
	  }
	menu.rstClock();
	while (this->_win.isRunning() && !(menu.finished()))
	{
		this->_win.clearWindow();
		menu.update(this->_win);
		this->_win.refreshWindow();
		this->_win.handleEvents();
		this->_socket.update(this->_parser);
	}
	return (true);
}

bool		Client::launch(std::string const &ip, int port)
{
	GameLoop		game;
	MetaThreader<GameLoop, void>	threader;

	this->_err.initialize();
	if (this->_win.openWindow(WIN_X, WIN_Y, "R-Type") == false)
	{
		this->_err.displayError("[Client::launch]", "Couldn't open render window");
		return (false);
	}
	this->_socket.setValues(ip, port, 4242);
	threader.start(&GameLoop::loadResources, &game, NULL);
	if (!(this->menu()))
		return (false);
	threader.waitThread();
	if (!(game.loop(this->_win)))
		return (false);
	return (true);
}

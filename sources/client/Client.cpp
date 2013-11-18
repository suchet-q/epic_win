#include "Client.h"


Client::Client(void)
{
}


Client::~Client(void)
{
}

void		Client::loading(MetaThreader<GameMenu, RenderWindow> &threader, GameMenu &menu, MetaMutex<> &mutex)
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
		while ((tmp -= 0.3f) >= 0.0f)
			ss << ". ";
		loading.setText(ss.str());
		mutex.Lock();
		this->_win.clearWindow();
		loading.update(0.15f, this->_win, 0);
		this->_win.refreshWindow();
		this->_win.handleEvents();
		mutex.Unlock();
	}
	threader.waitThread();
}

bool		Client::menu(GameLoop& game, MetaThreader<GameMenu, RenderWindow> &threaderMenu, MetaThreader<GameLoop, void> &threaderGame, MetaMutex<> &mutex)
{
	GameMenu	menu;

	menu.initParser(this->_parser);
	this->loading(threaderMenu, menu, mutex);
	menu.exception();
	threaderGame.start(&GameLoop::loadResources, &game, &(this->_clientID));
	if (!(this->_socket.connectTCP()))
		throw RuntimeException("[Client::launch]", "Couldn't connect to server");  
	menu.rstClock();
	while (!(menu.finished()))
	{
		try {
			mutex.Lock();
			this->_win.clearWindow();
			menu.update(this->_win);
			this->_win.refreshWindow();
			this->_win.handleEvents();
			mutex.Unlock();
			this->_socket.update(this->_parser);
		}
		catch (MinorException &e) {
			this->_err.displayError(e.method(), e.what());
		}
	}
	this->_socket.setUDPPort(menu.getUDPPort());
	this->_clientID = menu.getPlayerID();
	std::cout << "Before thread id " << (int)this->_clientID << std::endl;
	return (true);
}

int			Client::threadGame(MetaMutex<> *mutex)
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
	try {
		this->menu(game, threaderMenu, threaderGame, *mutex);
		game.exception();
		game.loop(this->_win, this->_parser, this->_socket, *mutex);
	}
	catch (RuntimeException &e) {
		threaderMenu.killThread();
		threaderGame.killThread();
		this->_err.displayError(e.method(), e.what());
		this->_win.closeWindow();
		return (false);
	}
	return (0);
}

bool		Client::launch(std::string const &ip, int port)
{
	MetaMutex<>								eventMutex;

	this->_socket.setValues(ip, port);
	eventMutex.initMutex();

	if (this->_win.openWindow(WIN_X, WIN_Y, "R-Type") == false)
	{
		this->_err.displayError("[Client::launch]", "Couldn't open render window");
		return (false);
	}
	this->_threadGame(&eventMutex);
	
	return (true);
}

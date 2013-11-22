#include "Client.h"
#include <X11/Xlib.h>

Client::Client(void)
{
	this->_finishedLoading = false;
}


Client::~Client(void)
{
}

void		Client::menuResources()
{
	this->_menu.initParser(this->_parser);
	this->_menu.loadResources(&this->_win);
	sf::Lock	lock(this->_mutex);
	this->_finishedLoading = true;
}

void		Client::gameResources()
{
	this->_game.loadResources(&(this->_clientID));
}

void		Client::update()
{
	this->loadingScreen();
	try {
		//this->_menu.exception();
		//this->_game.exception();		A mettre avant laancement game
		if (!(this->_socket.connectTCP()))
			throw RuntimeException("[Client::launch]", "Couldn't connect to server");  	
	}
	catch (RuntimeException &e) {
		
		this->_err.displayError(e.method(), e.what());
		this->_win.closeWindow();
	}
	this->_menu.rstClock();
	while (this->_win.isRunning() && !(this->_menu.finished()))
	{
		try {
			this->_win.clearWindow();
			this->_menu.update(this->_win);
			this->_win.refreshWindow();
			this->_win.handleEvents();
			this->_socket.update(this->_parser);
		}
		catch (MinorException &e) {
			this->_err.displayError(e.method(), e.what());
		}
	}
	this->_socket.setUDPPort(this->_menu.getUDPPort());
	this->_clientID = this->_menu.getPlayerID();
	try {
		this->_game.loop(this->_win, this->_parser, this->_socket);
	}
	catch (RuntimeException &e) {
		this->_err.displayError(e.method(), e.what());
		this->_win.closeWindow();
	}
	
}

void		Client::loadingScreen()
{
	WidgetText			loading;
	std::stringstream	ss;
	sf::Clock			clock;
	float				tmp;
	sf::Thread			gameResources(&Client::gameResources, this);
	sf::Thread			menuResources(&Client::menuResources, this);
	
	this->_win.setActive(true);
	loading.setStyle(sf::Text::Bold, 50, "Images/charlie_dotted.ttf", 0, 255, 0);
	loading.addActualSheet(0);
	loading.setPosition(sf::Vector2f(400, 340));
	//gameResources.launch();
	menuResources.launch();
	clock.restart();
	
	while (this->_win.isRunning())
	{
		this->_mutex.lock();
		if (this->_finishedLoading)
			break;
		this->_mutex.unlock();
		tmp = clock.getElapsedTime().asSeconds();
		if (clock.getElapsedTime().asSeconds() >= 1.2)
			clock.restart();
		ss.str("");
		ss << "Loading ";
		while ((tmp -= 0.3f) >= 0.0f)
			ss << ". ";
		loading.setText(ss.str());
		this->_win.clearWindow();
		//loading.update(0.15f, this->_win, 0);
		this->_win.refreshWindow();
	}
	this->_mutex.unlock();
}

void		Client::initializeThreads()
{
	sf::Thread	update(&Client::update, this);

	update.launch();
	try {
	  	this->_win.handleClosing();
	}
	catch (RuntimeException &e) {
		update.terminate();
		this->_err.displayError(e.method(), e.what());
		this->_win.closeWindow();
		std::cout << "Waiting Threads" << std::endl;
	}
}

bool		Client::launch(std::string const &ip, int port)
{
  XInitThreads();
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
	this->_socket.setValues(ip, port);
	this->_win.setActive(false);
	this->initializeThreads();
	return (true);
}

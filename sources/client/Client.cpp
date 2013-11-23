#include "Client.h"

#ifndef _WIN32
#include <X11/Xlib.h>
#endif

Client::Client(void)
{
	this->_finishedLoading = false;
}


Client::~Client(void)
{
}

void		Client::menuResources()
{
	sf::Context context;

  this->_menu.initParser(this->_parser);
  this->_menu.loadResources(&this->_win);
  sf::Lock	lock(this->_mutex);
  this->_finishedLoading = true;
}

void		Client::gameResources()
{
	this->_game.loadResources(&(this->_clientID), this->_win);
}

void		Client::update()
{
	sf::Thread			gameResources(&Client::gameResources, this);

	this->loadingScreen();
	if (!(this->_win.isRunning()))
		return;
	gameResources.launch();
	try {
		this->_menu.exception();
		if (!(this->_socket.connectTCP()))
			throw RuntimeException("[Client::launch]", "Couldn't connect to server");  	
	}
	catch (RuntimeException &e) {
		this->_err.displayError(e.method(), e.what());
		this->_win.closeWindow();
		gameResources.wait();
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
		this->_game.exception();
		this->_game.loop(this->_win, this->_parser, this->_socket);
	}
	catch (RuntimeException &e) {
		this->_err.displayError(e.method(), e.what());
		this->_win.closeWindow();
		gameResources.wait();
	}
	
}

void		Client::loadingScreen()
{
	WidgetText			loading;
	std::stringstream	ss;
	sf::Clock			clock;
	float				tmp;
	sf::Thread			menuResources(&Client::menuResources, this);
	
	this->_win.setActive(true);
	this->_win.lock(true);
	loading.setStyle(sf::Text::Bold, 50, "Images/charlie_dotted.ttf", 0, 255, 0);
	this->_win.lock(false);
	loading.addActualSheet(0);
	loading.setPosition(sf::Vector2f(400, 340));
	menuResources.launch();
	clock.restart();
	while (this->_win.isRunning())
	{
		if (clock.getElapsedTime().asSeconds() >= 1.2f)
			clock.restart();
		tmp = clock.getElapsedTime().asSeconds();
		this->_mutex.lock();
		if (this->_finishedLoading)
		{
			this->_mutex.unlock();
			break;
		}
		this->_mutex.unlock();
		ss.str("");
		ss << "Loading ";
		while ((tmp -= 0.3f) >= 0.0f)
		  ss << ". ";
		this->_win.lock(true); 
		loading.setText(ss.str());
		this->_win.lock(false);
		 this->_win.clearWindow();
		 loading.update(0.15f, this->_win, 0);
		 this->_win.refreshWindow();
	}
	menuResources.wait();
}

void		Client::initializeThreads()
{
	sf::Thread	update(&Client::update, this);

	update.launch();
	try {
	  	this->_win.handleClosing();
	}
	catch (RuntimeException &e) {
		this->_win.closeWindow();
		update.wait();
		std::cout << "Waiting Threads" << std::endl;
	}
}

bool		Client::launch(std::string const &ip, int port)
{
	THREADS_INITIALISATION;
	// XInitThreads();
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
	this->_err.setActive(false);
	this->_win.setActive(false);
	this->initializeThreads();
	return (true);
}

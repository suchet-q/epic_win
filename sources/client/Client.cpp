#include "Client.h"


Client::Client(void)
{
	this->_finishedLoading = false;
}


Client::~Client(void)
{
}

void		menuResourcesThread(void *client)
{
	(static_cast<Client *>(client))->menuResources();
}

void		gameResourcesThread(void *client)
{
	(static_cast<Client *>(client))->gameResources();
}

void		updateThread(void *client)
{
	(static_cast<Client *>(client))->update();
}

void		Client::menuResources()
{
	this->_menu.initParser(this->_parser);
	this->_menu.loadResources(&this->_win);
	this->_finishedLoading = true;
}

void		Client::gameResources()
{
	while (!this->_finishedLoading)
		sf::Sleep(0.25f);
	this->_game.loadResources(&(this->_clientID));
}

void		Client::update()
{
	this->loadingScreen();
	this->_menu.rstClock();
	try {
		this->_menu.exception();
		//this->_game.exception();		A mettre avant laancement game
		if (!(this->_socket.connectTCP()))
			throw RuntimeException("[Client::launch]", "Couldn't connect to server");  	
	}
	catch (RuntimeException &e) {
		this->_err.displayError(e.method(), e.what());
		this->_win.closeWindow();
	}
	while (this->_win.isRunning() && !(this->_menu.finished()))
	{
		try {
			this->_win.clearWindow();
			this->_win.lockMutex();
			this->_menu.update(this->_win);
			this->_win.unlockMutex();
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

	this->_win.setActive(true);
	loading.setStyle(sf::String::Bold, 50, "Images/charlie_dotted.ttf", 0, 255, 0);
	loading.addActualSheet(0);
	loading.setPosition(sf::Vector2f(400, 340));
	
	clock.Reset();
	
	while (this->_win.isRunning())
	{
	  if (this->_finishedLoading)
	    break;
		tmp = clock.GetElapsedTime();
		if (clock.GetElapsedTime() >= 1.2)
			clock.Reset();
		ss.str("");
		ss << "Loading ";
		while ((tmp -= 0.3f) >= 0.0f)
			ss << ". ";
		loading.setText(ss.str());
		this->_win.clearWindow();
		loading.update(0.15f, this->_win, 0);
		this->_win.refreshWindow();
	}
}

void		Client::initializeThreads()
{
	sf::Thread	gameResources(&gameResourcesThread, this);
	sf::Thread	menuResources(&menuResourcesThread, this);
	sf::Thread	update(&updateThread, this);
	
	menuResources.Launch();
	update.Launch();
	std::cout << "JE DOIS PASSER QUNE FOIS" << std::endl;
	gameResources.Launch();
	std::cout << "PAREIL POUR MOI" << std::endl;

	try {
	  	this->_win.handleClosing();
	}
	catch (RuntimeException &e) {
		update.Terminate();
		this->_err.displayError(e.method(), e.what());
		this->_win.closeWindow();
		std::cout << "Waiting Threads" << std::endl;
	}
}

bool		Client::launch(std::string const &ip, int port)
{
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

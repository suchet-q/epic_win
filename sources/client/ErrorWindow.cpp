#include "ErrorWindow.h"


ErrorWindow::ErrorWindow(void) : RenderWindow()
{
}


ErrorWindow::~ErrorWindow(void)
{
}

void		ErrorWindow::initialize()
{
	std::list<std::pair<sf::Vector2i, sf::Vector2i> >	subRects;
	std::list<sf::Vector2f>								pos;

	this->openWindow(450, 180, "error");
	this->_win->Show(false);
	this->_msg.setStyle(sf::String::Bold, 28, "Images/charlie_dotted.ttf", 255, 0, 0);
	this->_msg.addActualSheet(0);
	this->_method.setStyle(sf::String::Bold, 30, "Images/charlie_dotted.ttf", 142, 142, 142);
	this->_method.addActualSheet(0);

	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(0, 0), sf::Vector2i(200, 50)));
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(200, 0), sf::Vector2i(400, 50)));
	pos.push_back(sf::Vector2f(125, 100));
	pos.push_back(sf::Vector2f(WIN_X, WIN_Y));
	this->_ok.loadImage("Images/Ok.png");
	this->_ok.loadSprites(subRects);
	this->_ok.setPosition(pos);
	this->_ok.addActualSheet(0);
	this->_ok.setCallback("click", static_cast<RenderWindow *>(this), &RenderWindow::closeWindow);
}

void		ErrorWindow::displayError(const std::string &method, const std::string &error)
{
	this->_win->Show(true);
	this->_win->SetPosition(735, 450);
	this->_method.setText(method);
	this->_method.setPosition(sf::Vector2f((450 - this->_method.getRect().Right) / 2, 15));
	this->_msg.setText(error);
	this->_msg.setPosition(sf::Vector2f((450 - this->_msg.getRect().Right) / 2, 45));

	while (this->isRunning())
	{
		this->handleEvents();
		this->clearWindow();
		this->_msg.update(0.05f, (*this), 0);
		this->_method.update(0.05f, (*this), 0);
		this->_ok.update(0.05f, (*this), 0);
		this->refreshWindow();
	}
}

void		ErrorWindow::handleEvents()
{
	sf::Event	event;

	if (this->isRunning())
	{
		this->lockMutex();
		this->_winMutex.Lock();
		this->_lastInput = &this->_win->GetInput();
		this->_winMutex.Unlock();
		 this->unlockMutex();
		while (this->_win->GetEvent(event))
		{
			if (event.Type == sf::Event::Closed)
			{
				this->closeWindow();
				break;
			}
		}	
	}
}



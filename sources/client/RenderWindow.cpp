#include "RenderWindow.h"

RenderWindow::RenderWindow(void)
{
	this->_win = NULL;
	this->_nickname = "unknown";
	this->_getNick = false;
	this->_getMsg = false;
}


RenderWindow::~RenderWindow(void)
{
}

sf::RenderWindow*	RenderWindow::getWindow()
{
	return (this->_win);
}

bool		RenderWindow::isRunning()
{
	if (this->_win != NULL && this->_win->IsOpened())
		return (true);
	return (false);
}

bool		RenderWindow::openWindow(int x, int y, const std::string & name)
{
	if (this->_win == NULL)
	{
		if ((this->_win = new sf::RenderWindow(sf::VideoMode(x, y, 32), name, sf::Style::Close | sf::Style::Titlebar)) == NULL)
			return (false);
		this->_win->SetPosition(448, 156);
		this->_win->UseVerticalSync(true);
		return (true);
	}
	return (false);
}

void	RenderWindow::closeWindow()
{
	if (this->isRunning())
	{
		this->_win->Close();
		delete this->_win;
		this->_win = NULL;
	}
}

void		RenderWindow::lockMutex()
{
	this->_mutex.Lock();
}

void		RenderWindow::unlockMutex()
{
	this->_mutex.Unlock();
}

void		RenderWindow::handleClosing()
{
	sf::Event	event;

	while (42)
	{
		this->lockMutex();
		this->_lastInput = &this->_win->GetInput();
		this->unlockMutex();
		while (this->_win->GetEvent(event))
			if (event.Type == sf::Event::Closed)
				{
					throw RuntimeException("[RenderWindow::handleEvents]", "Closing Window. Bye Bye !");
					break;
				}
			else if (event.Type == sf::Event::TextEntered)
				this->_events.push_back(event);
		sf::Sleep(0.005f);
	}
}

void		RenderWindow::handleEvents()
{
	std::string	str;
	unsigned int		maxSize;
	std::list<sf::Event>::iterator it;

	for (it = this->_events.begin(); it != this->_events.end(); ++it)
		if (this->_getNick || this->_getMsg)
			{
				(this->_getNick) ? (str = this->_nickname) : (str = this->_msg);
				(this->_getNick) ? (maxSize = 15) : (maxSize = 50);
				if ((*it).Type == sf::Event::TextEntered)
				{
					if ((*it).Text.Unicode == '\b' && str.size() > 0)
						str.erase(str.size() - 1, 1);
					else if ((*it).Text.Unicode < 128 && str.size() < maxSize)
						str += static_cast<char>((*it).Text.Unicode);
				}
				(this->_getNick) ? (this->_nickname = str) : (this->_msg = str);
			}
}

void		RenderWindow::clearWindow()
{
	if (this->isRunning())
	{
		this->_win->Clear();
	}
}

void		RenderWindow::refreshWindow()
{
	if (this->isRunning())
	{
		this->_win->Display();
	}
}

void		RenderWindow::drawSprite(sf::Sprite &sprite)
{
	if (this->isRunning())
		this->_win->Draw(sprite);
}

const sf::Input&		RenderWindow::getInput()
{
	return (*this->_lastInput);
}

void					RenderWindow::clearMsg()
{
	this->_msg = "";
}

void					RenderWindow::drawText(sf::String &text)
{
	this->_win->Draw(text);
}

std::string				RenderWindow::getNickname()
{
	return (this->_nickname);
}

std::string				RenderWindow::getMsg()
{
	return (this->_msg);
}

void					RenderWindow::switchNick()
{
	this->_getNick = !(this->_getNick);
}

void					RenderWindow::switchMsg()
{
	this->_getMsg = !(this->_getMsg);
}

void					RenderWindow::disableNick()
{
	this->_getNick = false;
}

void					RenderWindow::disableMsg()
{
	this->_getMsg = false;
}

bool				RenderWindow::nickActive()
{
	return (this->_getNick);
}

bool				RenderWindow::msgActive()
{
	return (this->_getMsg);
}
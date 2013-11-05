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

void		RenderWindow::handleEvents()
{
	sf::Event	event;
	std::string	str;
	int			maxSize;

	if (this->isRunning())
	{
		while (this->_win->GetEvent(event))
		{
			if (event.Type == sf::Event::Closed)
			{
				this->closeWindow();
				break;
			}
			if (this->_getNick || this->_getMsg)
			{
				(this->_getNick) ? (str = this->_nickname) : (str = this->_msg);
				(this->_getNick) ? (maxSize = 15) : (maxSize = 50);
				if (event.Type == sf::Event::TextEntered)
				{
					if (event.Text.Unicode == '\b' && str.size() > 0)
						str.erase(str.size() - 1, 1);
					else if (event.Text.Unicode < 128 && str.size() < maxSize)
						str += static_cast<char>(event.Text.Unicode);
				}
				(this->_getNick) ? (this->_nickname = str) : (this->_msg = str);
			}
		}	
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
	return (this->_win->GetInput());
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

bool				RenderWindow::msgActive()
{
	return (this->_getMsg);
}
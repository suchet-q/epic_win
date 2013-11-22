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

void		RenderWindow::setActive(bool active)
{
  this->_win->setActive(active);
}

bool		RenderWindow::isRunning()
{
  bool		ret = false;

  if (this->_win != NULL && this->_win->isOpen())
    ret = true;
  return (ret);
}

bool		RenderWindow::openWindow(int x, int y, const std::string & name)
{
	if (this->_win == NULL)
	{
		if ((this->_win = new sf::RenderWindow(sf::VideoMode(x, y, 32), name, sf::Style::Close | sf::Style::Titlebar)) == NULL)
			return (false);
		this->_win->setPosition(sf::Vector2i(448, 156));
		this->_win->setVerticalSyncEnabled(true);
		return (true);
	}
	return (false);
}

void	RenderWindow::closeWindow()
{
	if (this->_win != NULL && this->_win->isOpen())
	{
		this->_win->close();
		delete this->_win;
		this->_win = NULL;
	}
}

void		RenderWindow::handleClosing()
{
  sf::Event	event;
  
  while (42)
    {
      while (42)
	  {
		  if (!this->_win->pollEvent(event))
				break;
			if (event.type == sf::Event::Closed)
			{
				throw RuntimeException("[RenderWindow::handleEvents]", "Closing Window. Bye Bye !");
				break;
			}
			else if (event.type == sf::Event::TextEntered)
				this->_events.push_back(event);
	  }
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
	      if ((*it).type == sf::Event::TextEntered)
		{
		  if ((*it).text.unicode == '\b' && str.size() > 0)
		    str.erase(str.size() - 1, 1);
		  else if ((*it).text.unicode < 128 && str.size() < maxSize)
		    str += static_cast<char>((*it).text.unicode);
		}
	      (this->_getNick) ? (this->_nickname = str) : (this->_msg = str);
	    }
}

void		RenderWindow::clearWindow()
{
	if (this->isRunning())
	{
	  this->_win->clear();
	}
}

void		RenderWindow::refreshWindow()
{
	if (this->isRunning())
	{
	  this->_win->display();
	}
}

void		RenderWindow::drawSprite(sf::Sprite &sprite)
{
  if (this->isRunning()) {
    this->_win->draw(sprite);
  }
}

void					RenderWindow::clearMsg()
{
	this->_msg = "";
}

void					RenderWindow::drawText(sf::Text &text)
{
  this->_win->draw(text);
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

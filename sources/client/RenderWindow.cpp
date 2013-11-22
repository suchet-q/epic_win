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

void		RenderWindow::lock(bool lock)
{
  if (lock)
    this->_mutex.lock();
  else
    this->_mutex.unlock();
}

void		RenderWindow::setActive(bool active)
{
  this->_win->setActive(active);
}

bool		RenderWindow::isRunning()
{
  sf::Lock	lock(this->_mutex);
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
		sf::sleep(sf::seconds(0.1f));
		this->_mutex.lock();
	while (this->_win->pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    {
	      this->_mutex.unlock();
	      throw RuntimeException("[RenderWindow::handleEvents]", "Closing Window. Bye Bye !");
	    }
	  else if (event.type == sf::Event::TextEntered)
	    this->_events.push_back(event);
	}
      this->_mutex.unlock();
    }

}

void		RenderWindow::handleEvents()
{
  sf::Lock lock(this->_mutex);
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
	  sf::Lock	lock(this->_mutex);
	  this->_win->clear();
	}
}

void		RenderWindow::refreshWindow()
{
	if (this->isRunning())
	{
	  sf::Lock	lock(this->_mutex);
	  this->_win->display();
	}
}


void		RenderWindow::drawSprite(sf::Sprite &sprite)
{
  if (this->isRunning()) {
    sf::Lock	lock(this->_mutex);
    this->_win->draw(sprite);
  }
}

void					RenderWindow::clearMsg()
{
	this->_msg = "";
}

void					RenderWindow::drawText(sf::Text &text)
{
  sf::Lock	lock(this->_mutex);
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
  sf::Lock	lock(this->_mutex);
  this->_getNick = !(this->_getNick);
}

void					RenderWindow::switchMsg()
{
  sf::Lock	lock(this->_mutex);
  this->_getMsg = !(this->_getMsg);
}

void					RenderWindow::disableNick()
{
  sf::Lock	lock(this->_mutex);
  this->_getNick = false;
}

void					RenderWindow::disableMsg()
{
  sf::Lock	lock(this->_mutex);
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

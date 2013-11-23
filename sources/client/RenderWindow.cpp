#include "RenderWindow.h"

RenderWindow::RenderWindow(void)
{
	this->_win = NULL;
	this->_nickname = "unknown";
	this->_getNick = false;
	this->_getMsg = false;
	this->_focused = true;
}


RenderWindow::~RenderWindow(void)
{
}

bool				RenderWindow::isFocused()
{
	return (this->_focused);
}

sf::RenderWindow*	RenderWindow::getWindow()
{
	return (this->_win);
}

sf::Mutex*			RenderWindow::getMutex()
{
	return (&this->_mutex);
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
	sf::Lock	lock(this->_mutex);

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
      sf::sleep(sf::seconds(0.05f));
      MUT_LOCK;
	  if (!(this->isRunning()))
		  break;
	while (this->_win->pollEvent(event) && this->isRunning())
	{
	  if (event.type == sf::Event::Closed)
	    {
	      MUT_UNLOCK;
	      throw RuntimeException("[RenderWindow::handleEvents]", "Closing Window. Bye Bye !");
	    }
	  else if (event.type == sf::Event::TextEntered)
	  {
		this->_evtMutex.lock();
	    this->_events.push_back(event);
		this->_evtMutex.unlock();
	  }
	  else if (event.type == sf::Event::LostFocus)
		this->_focused = false;
	  else if (event.type == sf::Event::GainedFocus)
		this->_focused = true;
	}
      MUT_UNLOCK;
    }

}

void		RenderWindow::handleEvents()
{
  sf::Lock lock(this->_mutex);
  sf::Lock lock2(this->_evtMutex);
  std::string	str;
  unsigned int		maxSize;
  std::list<sf::Event>::iterator it;

  for (it = this->_events.begin(); it != this->_events.end(); ++it)
	{
		if (this->_getNick || this->_getMsg)
		 {
			(this->_getNick) ? (str = this->_nickname) : (str = this->_msg);
			(this->_getNick) ? (maxSize = 15) : (maxSize = 50);
			if ((*it).type == sf::Event::TextEntered)
			{
				if ((*it).text.unicode == '\b' && str.size() > 0)
					str.erase(str.size() - 1, 1);
				else if ((*it).text.unicode >= 32 && (*it).text.unicode <= 126 && str.size() < maxSize)
					str += static_cast<char>((*it).text.unicode);
			}
			(this->_getNick) ? (this->_nickname = str) : (this->_msg = str);
		}
		it = this->_events.erase(it);
		if (it == this->_events.end())
			break;
  }
}

void		RenderWindow::clearWindow()
{
	sf::Lock	lock(this->_mutex);

	if (this->isRunning())
	  this->_win->clear();
}

void		RenderWindow::refreshWindow()
{
	sf::Lock	lock(this->_mutex);

	if (this->isRunning())
	  this->_win->display();
}


void		RenderWindow::drawSprite(sf::Sprite &sprite)
{
	sf::Lock	lock(this->_mutex);
	
	if (this->isRunning()) 
		this->_win->draw(sprite);
}

void					RenderWindow::clearMsg()
{
	this->_msg = "";
}

void					RenderWindow::drawText(sf::Text &text)
{
	sf::Lock	lock(this->_mutex);
	
	if (this->isRunning())
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

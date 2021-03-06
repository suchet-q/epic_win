#pragma once

#include	<boost/any.hpp>
#include	<SFML/Graphics.hpp>
#include	"AWidget.h"

class WidgetText : public AWidget
{
protected:
  sf::Text		_text;
  sf::Font		_font;
  float			_resetDelay;
  static sf::Mutex	_mutex;
  
  public:
  WidgetText(void);
  virtual ~WidgetText(void);
  
  virtual void	loadSprites(std::list<std::pair<sf::Vector2i, sf::Vector2i> > &);
  virtual void	setPosition(std::list<sf::Vector2f> &);
  virtual void	setAnimations(std::list<std::pair<sf::Vector2f, float> > &);
  virtual void	update(float, RenderWindow &, int);
  void			setText(const std::string &);
  void			setPosition(sf::Vector2f);
  void			setStyle(unsigned long, int, std::string const & = "",
				 unsigned char r = 255, unsigned char g = 255, unsigned char b = 255);
  boost::any	refreshText(std::list<boost::any>);
  void			setResetParameters(float);
  void			resetWidget();
  sf::FloatRect	getRect();
  int			getSize();
};


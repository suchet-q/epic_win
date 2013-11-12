#include "ErrorWindow.h"


ErrorWindow::ErrorWindow(void) : RenderWindow()
{
}


ErrorWindow::~ErrorWindow(void)
{
}

void		ErrorWindow::initialize()
{
	this->_msg.setStyle(sf::String::Bold, 28, "Images/charlie_dotted.ttf", 255, 0, 0);
	this->_msg.addActualSheet(0);
	this->_method.setStyle(sf::String::Bold, 30, "Images/charlie_dotted.ttf", 142, 142, 142);
	this->_method.addActualSheet(0);
}

void		ErrorWindow::displayError(const std::string &method, const std::string &error)
{
	this->openWindow(450, 180, "error");
	this->_win->SetPosition(735, 450);
	this->_method.setText(method);
	this->_method.setPosition(sf::Vector2f((450 - this->_method.getRect().Right) / 2, 15));
	this->_msg.setText(error);
	this->_msg.setPosition(sf::Vector2f((450 - this->_msg.getRect().Right) / 2, 45));
	while (this->isRunning())
	{
		this->clearWindow();
		this->_msg.update(0.05, (*this), 0);
		this->_method.update(0.05, (*this), 0);
		this->refreshWindow();
		this->handleEvents();
	}
}


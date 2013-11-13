#include "GameLoop.h"


GameLoop::GameLoop(void)
{
}

GameLoop::~GameLoop(void)
{
}

int		GameLoop::loadResources(void *arg)
{
	std::list<std::pair<sf::Vector2f, sf::Vector2f> >	subRects;
	std::list<std::pair<sf::Vector2f, float> >			anims;
	std::list<sf::Vector2f>								pos;

	subRects.push_back(std::pair<sf::Vector2f, sf::Vector2f>(sf::Vector2f(0, 0), sf::Vector2f(1024, 768)));
	subRects.push_back(std::pair<sf::Vector2f, sf::Vector2f>(sf::Vector2f(1024, 0), sf::Vector2f(2048, 768)));
	pos.push_back(sf::Vector2f(0, 0));
	pos.push_back(sf::Vector2f(1024, 0));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(-1024, 0), 15.0));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(-1024, 0), 30.0));
	this->_back1.loadImage("Images/back1.jpg");
	this->_back1.loadSprites(subRects);
	this->_back1.setPosition(pos);
	this->_back1.setAnimations(anims);
	this->_back1.addActualSheet(0);

	this->_back2.loadImage("Images/back2.png");
	this->_back2.loadSprites(subRects);
	this->_back2.setPosition(pos);
	anims.clear();
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(-1024, 0), 10.0));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(-1024, 0), 20.0));
	this->_back2.setAnimations(anims);
	this->_back2.addActualSheet(0);
	return (0);
}

void		GameLoop::drawHUB(RenderWindow &win, float elapsed)
{

}

void		GameLoop::drawEntities(RenderWindow &win, float elapsed)
{

}

void		GameLoop::drawBackground(RenderWindow &win, float elapsed)
{
	if (this->_back1.animationFinished(0))
	{
		std::list<sf::Vector2f>		pos;
		std::list<std::pair<sf::Vector2f, float> >			anims;

		pos.push_back(sf::Vector2f(1024, 0));
		pos.push_back(sf::Vector2f(0, 0));
		anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(-1024, 0), 30.0));
		anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(0, 0), 0.0));

		this->_back1.setPosition(pos);
		this->_back1.setAnimations(anims);
	}
	if (this->_back1.animationFinished(1))
	{
		std::list<sf::Vector2f>		pos;
		std::list<std::pair<sf::Vector2f, float> >			anims;

		pos.push_back(sf::Vector2f(0, 0));
		pos.push_back(sf::Vector2f(1024, 0));
		anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(0, 0), 0.0));
		anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(-1024, 0), 30.0));

		this->_back1.setPosition(pos);
		this->_back1.setAnimations(anims);
	}
		if (this->_back2.animationFinished(0))
	{
		std::list<sf::Vector2f>		pos;
		std::list<std::pair<sf::Vector2f, float> >			anims;

		pos.push_back(sf::Vector2f(1024, 0));
		pos.push_back(sf::Vector2f(0, 0));
		anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(-1024, 0), 20.0));
		anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(0, 0), 0.0));

		this->_back2.setPosition(pos);
		this->_back2.setAnimations(anims);
	}
	if (this->_back2.animationFinished(1))
	{
		std::list<sf::Vector2f>		pos;
		std::list<std::pair<sf::Vector2f, float> >			anims;

		pos.push_back(sf::Vector2f(0, 0));
		pos.push_back(sf::Vector2f(1024, 0));
		anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(0, 0), 0.0));
		anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(-1024, 0), 20.0));

		this->_back2.setPosition(pos);
		this->_back2.setAnimations(anims);
	}
	this->_back1.update(elapsed, win, 0);
	this->_back2.update(elapsed, win, 0);
}

bool		GameLoop::loop(RenderWindow &win)
{
	sf::Clock	clock;
	float		elapsed = 0.0;
	Managewindow		manager(win.getWindow());
	int		x = 100, y = 100;

	clock.Reset();
	while (win.isRunning())
	{
		win.clearWindow();
		this->drawBackground(win, elapsed);
		this->drawEntities(win, elapsed);
		this->drawHUB(win, elapsed);
		if (x < 450)
		{
			manager.SetItem(6, 10, x, y);
			manager.SetItem(7, 9, x, y + 50);
			manager.SetItem(8, 8, x, y + 100);
			manager.SetItem(9, 7, x, y + 150);
			manager.SetItem(10, 6, x, y + 200);
			manager.SetItem(11, 5, x, y + 250);
			manager.SetItem(12, 4, x, y + 300);
			manager.SetItem(13, 3, x, y + 350);
			manager.SetItem(15, 2, x, y + 400);
		}
		else
		{
			manager.SetItem(5, 10, x, y);
			manager.SetItem(5, 9, x, y + 50);
			manager.SetItem(5, 8, x, y + 100);
			manager.SetItem(5, 7, x, y + 150);
			manager.SetItem(5, 6, x, y + 200);
			manager.SetItem(5, 5, x, y + 250);
			manager.SetItem(5, 4, x, y + 300);
			manager.SetItem(5, 3, x, y + 350);
			manager.SetItem(5, 2, x, y + 400);
		}
		++x;

		++y;
		manager.Update();
		win.refreshWindow();
		win.handleEvents();
		elapsed = clock.GetElapsedTime();
		clock.Reset();
	}
	return (true);
}
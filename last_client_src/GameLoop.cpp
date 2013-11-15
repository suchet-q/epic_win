#include "GameLoop.h"


GameLoop::GameLoop(void)
{
	this->_lifeNb = 3;
	this->_scoreNb = 0;
	this->_exceptionOccured = false;
}

GameLoop::~GameLoop(void)
{
}

int		GameLoop::loadResources(void *arg)
{
	std::list<std::pair<sf::Vector2i, sf::Vector2i> >	subRects;
	std::list<std::pair<sf::Vector2f, float> >			anims;
	std::list<sf::Vector2f>								pos;

	try {
		subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(0, 0), sf::Vector2i(1024, 768)));
		subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(1024, 0), sf::Vector2i(2048, 768)));
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

		this->_life.setStyle(sf::String::Bold, 28, "Images/charlie_dotted.ttf", 255, 255, 255);
		this->_life.addActualSheet(0);
		this->_life.setPosition(sf::Vector2f(10, 0));

		this->_score.setStyle(sf::String::Bold, 28, "Images/charlie_dotted.ttf", 255, 255, 255);
		this->_score.addActualSheet(0);
		this->_score.setPosition(sf::Vector2f(10, 730));
	}
	catch (RuntimeException &e) {
		this->_exception = e;
		this->_exceptionOccured = true;
		return (-1);
	}
	this->_idClient = *(int *)arg;
	return (0);
}

void		GameLoop::exception()
{
	if (this->_exceptionOccured)
		throw this->_exception;
}

void		GameLoop::drawHUB(RenderWindow &win, float elapsed)
{
	std::stringstream	ss;

	ss << "Life : ";
	for (int i = 0; i < this->_lifeNb; ++i)
		ss << "<3 ";
	this->_life.setText(ss.str());
	ss.str("");
	ss << "Score : ";
	ss << this->_scoreNb;
	this->_score.setText(ss.str());
	this->_life.update(elapsed, win, 0);
	this->_score.update(elapsed, win, 0);
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

bool		GameLoop::loop(RenderWindow &win, Parser &parser, GameSocket &sock)
{
	sf::Clock	clock;
	float		elapsed = 0.0;
	float		timer = 2.0;
	Managewindow		manager(win.getWindow());
	int		x = 100, y = 100;

	if (!(sock.connectUDP()))
		throw RuntimeException("[GameLoop::loop]", "Can't create UDP Socket");
	clock.Reset();
	while (win.isRunning() && !(parser.getStartUDP()))
	{
		win.clearWindow();
		this->drawBackground(win, elapsed);
		win.refreshWindow();
		win.handleEvents();
		sock.update(parser);
		elapsed = clock.GetElapsedTime();
		timer += elapsed;
		if (timer >= 2.0)
		{
			timer -= 2.0;
			parser.addIDT(this->_idClient);
		}
		elapsed = clock.GetElapsedTime();
		clock.Reset();
	}
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
		sock.update(parser);
		elapsed = clock.GetElapsedTime();
		clock.Reset();
	}
	return (true);
}
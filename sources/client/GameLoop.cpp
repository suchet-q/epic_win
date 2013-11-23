#include "GameLoop.h"

GameLoop::GameLoop(void)
{
	this->_lifeNb = 3;
	this->_scoreNb = 0;
	this->_exceptionOccured = false;
	this->_vsyncDelay = 0.0f;
	this->_vsyncFactor = 1.0f / 60.0f;
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

		this->_life.setStyle(sf::Text::Bold, 28, "Images/charlie_dotted.ttf", 255, 255, 255);
		this->_life.addActualSheet(0);
		this->_life.setPosition(sf::Vector2f(10, 0));

		this->_score.setStyle(sf::Text::Bold, 28, "Images/charlie_dotted.ttf", 255, 255, 255);
		this->_score.addActualSheet(0);
		this->_score.setPosition(sf::Vector2f(10, 730));

		this->_fps.setStyle(sf::Text::Bold, 28, "Images/charlie_dotted.ttf", 255, 255, 255);
		this->_fps.addActualSheet(0);
		this->_fps.setPosition(sf::Vector2f(900, 730));
	}
	catch (RuntimeException &e) {
		this->_exception = e;
		this->_exceptionOccured = true;
		return (-1);
	}
	this->_idClient = (unsigned char *)arg;
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
	ss.str("");
	ss << "FPS : ";
	ss << static_cast<int>(1.0f / elapsed);
	this->_fps.setText(ss.str());
	this->_fps.update(elapsed, win, 0);
	this->_life.update(elapsed, win, 0);
	this->_score.update(elapsed, win, 0);
}

void		GameLoop::drawEntities(RenderWindow &win, float elapsed)
{
	this->_manager->Update();
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

boost::any	GameLoop::aff(std::list<boost::any> &args)
{
		unsigned short x, y, id;
		unsigned char type;

		type = boost::any_cast<unsigned char>(args.front());
		args.pop_front();
		id= boost::any_cast<unsigned short>(args.front());
		args.pop_front();
		x = boost::any_cast<unsigned short>(args.front());
		args.pop_front();
		y = boost::any_cast<unsigned short>(args.front());
		this->_manager->SetItem(type, id, x, y);
		return (0);
}

void		GameLoop::handleInputs(Parser &parser)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		parser.addINP(*this->_idClient, INP_LEFT);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		parser.addINP(*this->_idClient, INP_RIGHT);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		parser.addINP(*this->_idClient, INP_UP);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		parser.addINP(*this->_idClient, INP_DOWN);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		parser.addINP(*this->_idClient, INP_FIRE);
	}
}

boost::any	GameLoop::life(std::list<boost::any> &args)
{
	this->_lifeNb = boost::any_cast<unsigned char>(args.front());
	return (0);
}

boost::any	GameLoop::score(std::list<boost::any> &args)
{
	this->_scoreNb = boost::any_cast<unsigned short>(args.front());
	return (0);
}

bool		GameLoop::loop(RenderWindow &win, Parser &parser, GameSocket &sock)
{
	sf::Clock	clock;
	float		elapsed = 0.0;
	float		timer = 2.0;
	int		x = 100, y = 100;

	if (!(sock.connectUDP()))
		throw RuntimeException("[GameLoop::loop]", "Can't create UDP Socket");
	parser.addCallback(CMD_AFF, boost::bind(&GameLoop::aff, this, _1));
	parser.addCallback(CMD_LIF, boost::bind(&GameLoop::life, this, _1));
	parser.addCallback(CMD_SCR, boost::bind(&GameLoop::score, this, _1));
	
	this->_manager = new Managewindow(win.getWindow(), win.getMutex());
	this->_manager->InitDrawer();
	
	clock.restart();
	while (win.isRunning() && !(parser.getStartUDP()))
	{
		win.clearWindow();
		this->drawBackground(win, elapsed);
		win.refreshWindow();
		sock.update(parser);
		elapsed = clock.getElapsedTime().asSeconds();
		timer += elapsed;
		if (timer >= 2.0f)
		{
			timer -= 2.0f;
			parser.addIDT(*this->_idClient);
		}
		elapsed = clock.getElapsedTime().asSeconds();
		clock.restart();
	}
	timer = 0.0f;
	while (win.isRunning())
	{
		win.clearWindow();
		this->drawBackground(win, elapsed);
		this->drawEntities(win, elapsed);
		this->drawHUB(win, elapsed);
		win.refreshWindow();
		if ((timer += elapsed) >= 0.05f)
		{
			this->handleInputs(parser);
			timer = 0.0f;
		}
		sock.update(parser);
		elapsed = clock.getElapsedTime().asSeconds();
		clock.restart();
	}
	return (true);
}

#include "GameMenu.h"


GameMenu::GameMenu(void)
{
	this->_totalLobbies = 0;
	this->_finished = false;
	this->_exceptionOccured = false;
	this->_sheetSkipped = false;
	this->_antiSpam = false;
}


GameMenu::~GameMenu(void)
{
	for (std::list<AWidget *>::iterator it = this->_widgets.begin(); it != this->_widgets.end(); ++it)
		delete (*it);
	for (std::list<std::pair<WidgetSwitch *, WidgetSwitch *> >::iterator it = this->_lobbiesFrame.begin(); it != this->_lobbiesFrame.end(); ++it)
	{
		delete (*it).first;
		delete (*it).second;
	}
	for (std::list<WidgetText *>::iterator it = this->_lobbiesText.begin(); it != this->_lobbiesText.end(); ++it)
		delete (*it);
	for (std::list<WidgetSwitch *>::iterator it = this->_playersFrame.begin(); it != this->_playersFrame.end(); ++it)
		delete (*it);
	for (std::list<WidgetText *>::iterator it = this->_playersText.begin(); it != this->_playersText.end(); ++it)
		delete (*it);
	for (std::list<WidgetText *>::iterator it = this->_msgText.begin(); it != this->_msgText.end(); ++it)
		delete (*it);
	//delete this->_input;
	//delete this->_inputMsg;
	//delete this->_typingBar;
	//delete this->_playersLabel;
	//delete this->_lobbiesLabel;
}

void		GameMenu::loadImages()
{
  //	sf::Context	context;
	std::list<std::pair<sf::Vector2i, sf::Vector2i> >	subRects;
	std::list<std::pair<sf::Vector2f, float> >			anims;
	std::list<sf::Vector2f>								pos;
	WidgetImage*	transition = new WidgetImage, *logo = new WidgetImage, *fullLogo = new WidgetImage;

	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(0, 0), sf::Vector2i(105, 153)));
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(105, 0), sf::Vector2i(210, 153)));
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(210, 0), sf::Vector2i(315, 153)));
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(315, 0), sf::Vector2i(420, 153)));
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(420, 0), sf::Vector2i(525, 153)));
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(525, 0), sf::Vector2i(630, 153)));
	pos.push_back(sf::Vector2f(WIN_X - 135, WIN_Y / 2 - 75));
	pos.push_back(sf::Vector2f(WIN_X - 135, WIN_Y / 2 - 75));
	pos.push_back(sf::Vector2f(WIN_X - 135, WIN_Y / 2 - 75));
	pos.push_back(sf::Vector2f(WIN_X - 135, WIN_Y / 2 - 75));
	pos.push_back(sf::Vector2f(WIN_X - 135, WIN_Y / 2 - 75));
	pos.push_back(sf::Vector2f(WIN_X - 135, WIN_Y / 2 - 75));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f((WIN_X - 570) / 2, WIN_Y / 2 - 75), 2.5f));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f((WIN_X - 570) / 2, WIN_Y / 2 - 75), 2.5f));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f((WIN_X - 570) / 2, WIN_Y / 2 - 75), 2.5f));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f((WIN_X - 570) / 2, WIN_Y / 2 - 75), 2.5f));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f((WIN_X - 570) / 2, WIN_Y / 2 - 75), 2.5f));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f((WIN_X - 570) / 2, WIN_Y / 2 - 75), 2.5f));
	logo->loadImage("Images/rtype-logo.bmp");
	logo->loadSprites(subRects);
	logo->setPosition(pos);
	logo->setAnimations(anims);
	logo->setTimeToLive(6.0);
	logo->addActualSheet(0);
	anims.clear();
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f((WIN_X - 570) / 2, WIN_Y / 2 - 75), 2.5f));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f((WIN_X - 570) / 2 + 85, WIN_Y / 2 - 75), 2.5f));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f((WIN_X - 570) / 2 + 150, WIN_Y / 2 - 75), 2.5f));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f((WIN_X - 570) / 2 + 255, WIN_Y / 2 - 75), 2.5f));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f((WIN_X - 570) / 2 + 360, WIN_Y / 2 - 75), 2.5f));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f((WIN_X - 570) / 2 + 465, WIN_Y / 2 - 75), 2.5f));
	logo->setAnimations(anims);

	subRects.clear();
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(0, 0), sf::Vector2i(640, 153)));
	pos.clear();
	pos.push_back(sf::Vector2f(WIN_X / 2 - 320, 10));
	fullLogo->loadImage("Images/rtype-logo.bmp");
	fullLogo->loadSprites(subRects);
	fullLogo->setPosition(pos);
	fullLogo->setTransitionTime(2.0, false);
	fullLogo->setDelay(6.0);
	fullLogo->addActualSheet(0);
	fullLogo->addActualSheet(1);

	subRects.clear();
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(0, 0), sf::Vector2i(WIN_X, WIN_Y)));
	transition->loadImage("Images/transition.bmp");
	transition->loadSprites(subRects);
	transition->setTransitionTime(2.0, true);
	transition->setDelay(5.0);
	transition->addActualSheet(0);
	transition->addActualSheet(1);
	transition->addActualSheet(2);
	transition->addActualSheet(3);
	this->_widgets.push_back(logo);
	this->_widgets.push_back(transition);
	this->_widgets.push_back(fullLogo);
}

bool		GameMenu::finished()
{
	return (this->_finished);
}

boost::any		GameMenu::setFinished(std::list<boost::any> args)
{
	if (boost::any_cast<unsigned char>(args.front()) != 0)
	{
		this->_finished = true;
		this->_udpPort = boost::any_cast<unsigned int>(args.back());
	}
	else
		throw MinorException("[GameMenu::setFinished]", "Game was not started");
	return (0);
}

unsigned char	GameMenu::getPlayerID()
{
	return (this->_playerId);
}

int			GameMenu::getUDPPort()
{
	return (this->_udpPort);
}

void		GameMenu::loadButtons(RenderWindow *win)
{
  //	sf::Context	context;
	WidgetButton*	play = new WidgetButton, *options = new WidgetButton, *quit = new WidgetButton, *back = new WidgetButton, *refresh = new WidgetButton, 
	*create = new WidgetButton, *join = new WidgetButton, *prev = new WidgetButton, *next = new WidgetButton;
	WidgetSwitch*	musicOn = new WidgetSwitch, *musicOff = new WidgetSwitch, *soundOn = new WidgetSwitch, *soundOff = new WidgetSwitch;
	WidgetImage *lobbyFrame = new WidgetImage, *statFrame = new WidgetImage, *lobbyBack = new WidgetImage, *statBack = new WidgetImage;
	std::list<std::pair<sf::Vector2i, sf::Vector2i> >	subRects;
	std::list<std::pair<sf::Vector2f, float> >			anims;
	std::list<sf::Vector2f>								pos;
	Sheets *sheet = &(this->_sheets);

	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(0, 0), sf::Vector2i(200, 50)));
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(200, 0), sf::Vector2i(400, 50)));
	pos.push_back(sf::Vector2f(WIN_X, WIN_Y / 2 - 25 + 80));
	pos.push_back(sf::Vector2f(WIN_X, WIN_Y));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(WIN_X / 2 - 100, WIN_Y / 2 - 25 + 80), 0.5f));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(WIN_X / 2 - 100, WIN_Y / 4 - 25 + 80), 0.5f));
	play->loadImage("Images/play.png");
	play->loadSprites(subRects);
	play->setPosition(pos);
	play->setAnimations(anims);
	play->setDelay(6.5);
	play->addActualSheet(0);
	play->setDestinationSheet(2);
	play->setUnclickable();
	play->setSheet(sheet);
	play->setCallback("animationFinished", play, &WidgetButton::setClickable);
	play->setCallback("click", play, &WidgetButton::loadDestinationSheet);
	play->setCallback("click", this, &GameMenu::clearLobbies);
	play->setCallback("click", this->_parser, &Parser::addNBL);
	play->setCallback("click", this->_parser, &Parser::addNBP);

	anims.clear();
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(WIN_X / 2 - 100, WIN_Y / 2 - 25 + 80), 0.5f));
	options->loadImage("Images/options.png");
	options->loadSprites(subRects);
	options->setPosition(pos);
	options->setAnimations(anims);
	options->setDelay(7.5);
	options->setResetParameters(1.0);
	options->setUnclickable();
	options->addActualSheet(0);
	options->setDestinationSheet(1);
	options->setSheet(sheet);
	options->setCallback("click", options, &WidgetButton::loadDestinationSheet);
	options->setCallback("animationFinished", options, &WidgetButton::setClickable);

	anims.clear();
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(WIN_X / 2 - 100, WIN_Y / 2 - 25 + 80), 0.5f));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(WIN_X / 2 - 100, (WIN_Y / 4) * 3 - 25 + 80), 0.5f));
	quit->loadImage("Images/exit.png");
	quit->loadSprites(subRects);
	quit->setPosition(pos);
	quit->setAnimations(anims);
	quit->setDelay(7.0);
	quit->setResetParameters(0.5);
	quit->addActualSheet(0);
	quit->setUnclickable();
	quit->setCallback("click", win, &RenderWindow::closeWindow);
	quit->setCallback("animationFinished", quit, &WidgetButton::setClickable);
	
	subRects.clear();
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(0, 0), sf::Vector2i(400, 50)));
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(400, 0), sf::Vector2i(800, 50)));
	pos.clear();
	pos.push_back(sf::Vector2f(-200, WIN_Y / 2 - 25 + 80));
	pos.push_back(sf::Vector2f(WIN_X, WIN_Y));
	anims.clear();
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(WIN_X / 2 - 200, WIN_Y / 2 - 25 + 80), 0.5f));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(WIN_X / 2 - 200, WIN_Y / 4 - 25 + 80), 0.5f));
	musicOn->loadImage("Images/musicOn.png");
	musicOn->loadSprites(subRects);
	musicOn->setPosition(pos);
	musicOn->setAnimations(anims);
	musicOn->addActualSheet(1);
	musicOn->setCallback("animationFinished", musicOn, &WidgetSwitch::setClickable);
	musicOn->setCallback("click", musicOn, &WidgetSwitch::setUnvisible);
	musicOn->setCallback("click", musicOff, &WidgetSwitch::setVisible);
	musicOn->setCallback("click", musicOff, &WidgetSwitch::setClickable);
	musicOn->setCallback("click", musicOff, &WidgetSwitch::cancelAnimations);
	musicOn->setCallback("click", SoundPool::getInstance(), &SoundPool::disableMusic);

	musicOff->loadImage("Images/musicOff.png");
	musicOff->loadSprites(subRects);
	musicOff->setPosition(pos);
	musicOff->setAnimations(anims);
	musicOff->addActualSheet(1);
	musicOff->setUnvisible();
	musicOff->setCallback("animationFinished", musicOff, &WidgetSwitch::setClickable);
	musicOff->setCallback("click", musicOff, &WidgetSwitch::setUnvisible);
	musicOff->setCallback("click", musicOn, &WidgetSwitch::setVisible);
	musicOff->setCallback("click", musicOn, &WidgetSwitch::setClickable);
	musicOff->setCallback("click", musicOn, &WidgetSwitch::cancelAnimations);
	musicOff->setCallback("click", SoundPool::getInstance(), &SoundPool::enableMusic);
	anims.clear();
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(WIN_X / 2 - 200, WIN_Y / 2 - 25 + 80), 0.5f));
	soundOn->loadImage("Images/soundOn.png");
	soundOn->loadSprites(subRects);
	soundOn->setPosition(pos);
	soundOn->setAnimations(anims);
	soundOn->addActualSheet(1);
	soundOn->setDelay(0.5);
	soundOn->setResetParameters(0.5);
	soundOn->setCallback("animationFinished", soundOn, &WidgetSwitch::setClickable);
	soundOn->setCallback("click", soundOn, &WidgetSwitch::setUnvisible);
	soundOn->setCallback("click", soundOff, &WidgetSwitch::setVisible);
	soundOn->setCallback("click", soundOff, &WidgetSwitch::setClickable);
	soundOn->setCallback("click", soundOff, &WidgetSwitch::cancelAnimations);
	soundOn->setCallback("click", SoundPool::getInstance(), &SoundPool::disableSound);

	soundOff->loadImage("Images/soundOff.png");
	soundOff->loadSprites(subRects);
	soundOff->setPosition(pos);
	soundOff->setAnimations(anims);
	soundOff->addActualSheet(1);
	soundOff->setUnvisible();
	soundOff->setDelay(0.5);
	soundOff->setResetParameters(0.5);
	soundOff->setCallback("animationFinished", soundOff, &WidgetSwitch::setClickable);
	soundOff->setCallback("click", soundOff, &WidgetSwitch::setUnvisible);
	soundOff->setCallback("click", soundOn, &WidgetSwitch::setVisible);
	soundOff->setCallback("click", soundOn, &WidgetSwitch::setClickable);
	soundOff->setCallback("click", soundOn, &WidgetSwitch::cancelAnimations);
	soundOff->setCallback("click", SoundPool::getInstance(), &SoundPool::enableSound);

	subRects.clear();
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(0, 0), sf::Vector2i(200, 50)));
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(200, 0), sf::Vector2i(400, 50)));
	pos.clear();
	pos.push_back(sf::Vector2f(WIN_X + 200, WIN_Y - 70));
	pos.push_back(sf::Vector2f(WIN_X, WIN_Y));
	anims.clear();
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(WIN_X - 220, WIN_Y -70), 0.2f));
	back->loadImage("Images/back.png");
	back->loadSprites(subRects);
	back->setPosition(pos);
	back->setAnimations(anims);
	back->addActualSheet(1);
	back->addActualSheet(2);
	back->setDestinationSheet(0);
	back->setSheet(sheet);
	back->setCallback("click", back, &WidgetButton::loadDestinationSheet);
	back->setCallback("animationFinished", back, &WidgetButton::setClickable);

	pos.clear();
	pos.push_back(sf::Vector2f(WIN_X + 200, 520));
	pos.push_back(sf::Vector2f(WIN_X, WIN_Y));
	anims.clear();
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(WIN_X - 305, 520), 0.5f));
	create->loadImage("Images/create.png");
	create->loadSprites(subRects);
	create->setPosition(pos);
	create->setAnimations(anims);
	create->addActualSheet(2);
	create->setCallback("animationFinished", create, &WidgetButton::setClickable);
	create->setCallback("click", this, &GameMenu::clearPlayers);
	create->setCallback("click", this, &GameMenu::createLobby);

	pos.clear();
	pos.push_back(sf::Vector2f(WIN_X + 200, 460));
	pos.push_back(sf::Vector2f(WIN_X, WIN_Y));
	anims.clear();
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(WIN_X - 305, 460), 0.5f));
	join->loadImage("Images/join.png");
	join->loadSprites(subRects);
	join->setPosition(pos);
	join->setAnimations(anims);
	join->addActualSheet(2);
	join->setCallback("animationFinished", join, &WidgetButton::setClickable);
	join->setCallback("click", this, &GameMenu::clearPlayers);
	join->setCallback("click", this, &GameMenu::joinLobby);

	pos.clear();
	pos.push_back(sf::Vector2f(82, 768 + 50));
	pos.push_back(sf::Vector2f(WIN_X, WIN_Y));
	anims.clear();
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(82, 685), 0.5f));
	prev->loadImage("Images/prev.png");
	prev->loadSprites(subRects);
	prev->setPosition(pos);
	prev->setAnimations(anims);
	prev->addActualSheet(2);
	prev->setCallback("animationFinished", prev, &WidgetButton::setClickable);
	pos.clear();
	pos.push_back(sf::Vector2f(302, 768 + 50));
	pos.push_back(sf::Vector2f(WIN_X, WIN_Y));
	anims.clear();
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(302, 685), 0.5f));
	next->loadImage("Images/next.png");
	next->loadSprites(subRects);
	next->setPosition(pos);
	next->setAnimations(anims);
	next->addActualSheet(2);
	next->setCallback("animationFinished", next, &WidgetButton::setClickable);

	subRects.clear();
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(0, 0), sf::Vector2i(250, 50)));
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(250, 0), sf::Vector2i(500, 50)));
	pos.clear();
	pos.push_back(sf::Vector2f(WIN_X + 250, 580));
	pos.push_back(sf::Vector2f(WIN_X, WIN_Y));
	anims.clear();
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(WIN_X - 355, 580), 0.5f));
	refresh->loadImage("Images/refresh.png");
	refresh->loadSprites(subRects);
	refresh->setPosition(pos);
	refresh->setAnimations(anims);
	refresh->addActualSheet(2);
	refresh->setCallback("animationFinished", refresh, &WidgetButton::setClickable);
	refresh->setCallback("click", this, &GameMenu::clearLobbies);
	refresh->setCallback("click", this->_parser, &Parser::addNBL);
	refresh->setCallback("click", this->_parser, &Parser::addNBP);

	subRects.clear();
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(0, 0), sf::Vector2i(1000, 800)));
	pos.clear();
	pos.push_back(sf::Vector2f(-1000, 25));
	anims.clear();
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(70, 25), 0.5f));
	lobbyFrame->loadImage("Images/frame_lobby.png");
	lobbyFrame->loadSprites(subRects, 0, 255, 0);
	lobbyFrame->setPosition(pos);
	lobbyFrame->setAnimations(anims);
	lobbyFrame->addActualSheet(2);

	pos.clear();
	pos.push_back(sf::Vector2f(70, 25));
	lobbyBack->loadImage("Images/frame_lobby_back.png");
	lobbyBack->loadSprites(subRects, 0, 255, 0);
	lobbyBack->setPosition(pos);
	lobbyBack->setTransitionTime(2.0, false);
	lobbyBack->setDelay(0.5);
	lobbyBack->setResetParameters(0.5, 2.0);
	lobbyBack->addActualSheet(2);

	pos.clear();
	pos.push_back(sf::Vector2f(70, 25));
	statBack->loadImage("Images/frame_stats_back.png");
	statBack->loadSprites(subRects, 0, 255, 0);
	statBack->setPosition(pos);
	statBack->setTransitionTime(2.0, false);
	statBack->setDelay(0.5);
	statBack->setResetParameters(0.5, 2.0);
	statBack->addActualSheet(2);

	pos.clear();
	pos.push_back(sf::Vector2f(WIN_X + 1000, 25));
	statFrame->loadImage("Images/frame_stats.png");
	statFrame->loadSprites(subRects, 0, 255, 0);
	statFrame->setPosition(pos);
	statFrame->setAnimations(anims);
	statFrame->addActualSheet(2);

	sheet->addWidgetToSheet(0, play,  &WidgetButton::resetWidget);
	sheet->addWidgetToSheet(0, play,  &WidgetButton::setUnclickable);
	sheet->addWidgetToSheet(0, options,  &WidgetButton::resetWidget);
	sheet->addWidgetToSheet(0, options,  &WidgetButton::setUnclickable);
	sheet->addWidgetToSheet(0, quit,  &WidgetButton::resetWidget);
	sheet->addWidgetToSheet(0, quit,  &WidgetButton::setUnclickable);
	sheet->addWidgetToSheet(0, win,  &RenderWindow::disableNick);
	sheet->addWidgetToSheet(1, soundOn,  &WidgetSwitch::resetWidget);
	sheet->addWidgetToSheet(1, soundOn,  &WidgetSwitch::setUnclickable);
	sheet->addWidgetToSheet(1, soundOff,  &WidgetSwitch::resetWidget);
	sheet->addWidgetToSheet(1, soundOff,  &WidgetSwitch::setUnclickable);
	sheet->addWidgetToSheet(1, musicOn,  &WidgetSwitch::resetWidget);
	sheet->addWidgetToSheet(1, musicOn,  &WidgetSwitch::setUnclickable);
	sheet->addWidgetToSheet(1, musicOff,  &WidgetSwitch::resetWidget);
	sheet->addWidgetToSheet(1, musicOff,  &WidgetSwitch::setUnclickable);
	sheet->addWidgetToSheet(1, back,  &WidgetButton::resetWidget);
	sheet->addWidgetToSheet(1, back,  &WidgetButton::setUnclickable);
	sheet->addWidgetToSheet(2, back,  &WidgetButton::resetWidget);
	sheet->addWidgetToSheet(2, back,  &WidgetButton::setUnclickable);
	sheet->addWidgetToSheet(2, lobbyFrame, &WidgetImage::resetWidget);
	sheet->addWidgetToSheet(2, statFrame, &WidgetImage::resetWidget);
	sheet->addWidgetToSheet(2, lobbyBack, &WidgetImage::resetWidget);
	sheet->addWidgetToSheet(2, statBack, &WidgetImage::resetWidget);
	sheet->addWidgetToSheet(2, refresh,  &WidgetButton::resetWidget);
	sheet->addWidgetToSheet(2, refresh,  &WidgetButton::setUnclickable);
	sheet->addWidgetToSheet(2, join,  &WidgetButton::resetWidget);
	sheet->addWidgetToSheet(2, join,  &WidgetButton::setUnclickable);
	sheet->addWidgetToSheet(2, create,  &WidgetButton::resetWidget);
	sheet->addWidgetToSheet(2, create,  &WidgetButton::setUnclickable);
	sheet->addWidgetToSheet(2, prev,  &WidgetButton::resetWidget);
	sheet->addWidgetToSheet(2, prev,  &WidgetButton::setUnclickable);
	sheet->addWidgetToSheet(2, next,  &WidgetButton::resetWidget);
	sheet->addWidgetToSheet(2, next,  &WidgetButton::setUnclickable);
	sheet->addWidgetToSheet(2, win,  &RenderWindow::disableMsg);
	sheet->addWidgetToSheet(3, win,  &RenderWindow::disableNick);

	this->_widgets.push_back(play);
	this->_widgets.push_back(options);
	this->_widgets.push_back(quit);
	this->_widgets.push_back(musicOn);
	this->_widgets.push_back(musicOff);
	this->_widgets.push_back(soundOn);
	this->_widgets.push_back(soundOff);
	this->_widgets.push_back(back);
	this->_widgets.push_back(lobbyBack);
	this->_widgets.push_back(statBack);
	this->_widgets.push_back(refresh);
	this->_widgets.push_back(create);
	this->_widgets.push_back(join);
	this->_widgets.push_back(prev);
	this->_widgets.push_back(next);
	this->_widgets.push_back(lobbyFrame);
	this->_widgets.push_back(statFrame);

	this->loadText(win);
	this->loadLobbies(join, win);
}

void		GameMenu::loadText(RenderWindow *win)
{
  //	sf::Context	context;
	WidgetText	*statistics = new WidgetText, *players = new WidgetText, *lobbies = new WidgetText, *nickname = new WidgetText, *highscore = new WidgetText;
	WidgetButton *input = new WidgetButton;
	std::list<std::pair<sf::Vector2i, sf::Vector2i> >	subRects;
	std::list<sf::Vector2f>								pos;
	Sheets *sheet = &(this->_sheets);
	statistics->setText("Statistics : ");
	statistics->setPosition(sf::Vector2f(740, 50));
	statistics->addActualSheet(2);
	statistics->setStyle(sf::Text::Bold, 30, "Images/charlie_dotted.ttf", 0, 0, 0);
	statistics->setDelay(1.2f);
	statistics->setResetParameters(1.2f);

	players->setText("Online players : 1");
	players->setPosition(sf::Vector2f(740, 90));
	players->addActualSheet(2);
	players->setStyle(sf::Text::Bold, 25, "Images/charlie_dotted.ttf", 0, 0, 0);
	players->setDelay(1.2f);
	players->setResetParameters(1.2f);
	this->_playersLabel = players;

	lobbies->setText("Open lobbies : 0");
	lobbies->setPosition(sf::Vector2f(740, 125));
	lobbies->addActualSheet(2);
	lobbies->setStyle(sf::Text::Bold, 25, "Images/charlie_dotted.ttf", 0, 0, 0);
	lobbies->setDelay(1.2f);
	lobbies->setResetParameters(1.2f);
	this->_lobbiesLabel = lobbies;

	highscore->setText("High score : 1337");
	highscore->setPosition(sf::Vector2f(740, 160));
	highscore->addActualSheet(2);
	highscore->setStyle(sf::Text::Bold, 25, "Images/charlie_dotted.ttf", 0, 0, 0);
	highscore->setDelay(1.2f);
	highscore->setResetParameters(1.2f);

	nickname->setText("Nickname : ");
	nickname->setPosition(sf::Vector2f(740, 240));
	nickname->addActualSheet(2);
	nickname->setStyle(sf::Text::Bold, 30, "Images/charlie_dotted.ttf", 0, 0, 0);
	nickname->setDelay(1.2f);
	nickname->setResetParameters(1.2f);

	this->_input = new WidgetText;
	this->_input->setText("");
	this->_input->setPosition(sf::Vector2f(752, 278));
	this->_input->addActualSheet(2);
	this->_input->setStyle(sf::Text::Bold, 22, "Images/charlie_dotted.ttf", 0, 0, 0);
	this->_input->setDelay(1.2f);
	this->_input->setResetParameters(1.2f);

	this->_typingBar = new WidgetTypingBar;

	subRects.clear();
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(0, 0), sf::Vector2i(180, 30)));
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(0, 0), sf::Vector2i(179, 30)));
	pos.clear();
	pos.push_back(sf::Vector2f(745, 280));
	pos.push_back(sf::Vector2f(WIN_X, WIN_Y));
	input->loadImage("Images/input.png");
	input->loadSprites(subRects);
	input->setPosition(pos);
	input->setDelay(1.2f);
	input->setResetParameters(1.2f);
	input->addActualSheet(2);
	input->setCallback("click", win, &RenderWindow::switchNick);
	input->setCallback("click", this->_typingBar, &WidgetTypingBar::switchActivate);
	input->setCallback("click", this, &GameMenu::setNickname);

	sheet->addWidgetToSheet(2, statistics, &WidgetText::resetWidget);
	sheet->addWidgetToSheet(2, highscore, &WidgetText::resetWidget);
	sheet->addWidgetToSheet(2, lobbies, &WidgetText::resetWidget);
	sheet->addWidgetToSheet(2, players, &WidgetText::resetWidget);
	sheet->addWidgetToSheet(2, nickname, &WidgetText::resetWidget);
	sheet->addWidgetToSheet(2, this->_input, &WidgetText::resetWidget);
	sheet->addWidgetToSheet(2, input, &WidgetButton::resetWidget);
	sheet->addWidgetToSheet(0, this->_typingBar,  &WidgetTypingBar::desactivate);
	sheet->addWidgetToSheet(2, this->_typingBar,  &WidgetTypingBar::desactivate);
	sheet->addWidgetToSheet(3, this->_typingBar,  &WidgetTypingBar::desactivate);

	this->_widgets.push_back(statistics);
	this->_widgets.push_back(players);
	this->_widgets.push_back(lobbies);
	this->_widgets.push_back(nickname);
	this->_widgets.push_back(highscore);
	this->_widgets.push_back(input);
	this->_widgets.push_back(this->_input);
}

void		GameMenu::loadLobbies(WidgetButton *join, RenderWindow *win)
{
  //	sf::Context	context;
	WidgetSwitch	*lobbyOff, *lobbyOn, *input = new WidgetSwitch;
	WidgetText		*text;
	WidgetImage		*lobby_top_left = new WidgetImage, *lobby_top_right = new WidgetImage, *lobby_bot_left = new WidgetImage, *lobby_bot_right = new WidgetImage, *juda = new WidgetImage;
	WidgetImage		*lobby_topleft = new WidgetImage, *lobby_topright = new WidgetImage, *lobby_botleft = new WidgetImage, *lobby_botright = new WidgetImage;
	WidgetButton	*start = new WidgetButton, *leave = new WidgetButton, *send = new WidgetButton;
	std::list<std::pair<sf::Vector2i, sf::Vector2i> >	subRects;
	std::list<sf::Vector2f>								pos;
	std::list<std::pair<sf::Vector2f, float> >			anims;
	std::list<std::pair<WidgetSwitch *, WidgetSwitch *> >::iterator		it;
	std::list<std::pair<WidgetSwitch *, WidgetSwitch *> >::iterator		it2;
	Sheets *sheet = &(this->_sheets);

	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(0, 0), sf::Vector2i(545, 50)));
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(545, 0), sf::Vector2i(1090, 50)));
	for (int i = 0; i <= 10; ++i)
	{
		lobbyOff = new WidgetSwitch;
		lobbyOn = new WidgetSwitch;
		text = new WidgetText;

		pos.clear();
		pos.push_back(sf::Vector2f(116.0f, static_cast<float>(52 + i * 54)));
		pos.push_back(sf::Vector2f(static_cast<float>(WIN_X), static_cast<float>(WIN_Y)));
		lobbyOn->loadImage("Images/lobby_unselected.png");
		lobbyOn->loadSprites(subRects);
		lobbyOn->setPosition(pos);
		lobbyOn->setDelay(1.2f);
		lobbyOn->setResetParameters(1.2f);
		lobbyOn->addActualSheet(2);
		lobbyOn->setCallback("click", lobbyOn, &WidgetSwitch::setUnvisible);
		lobbyOn->setCallback("click", lobbyOff, &WidgetSwitch::setVisible);
		lobbyOn->setCallback("click", lobbyOff, &WidgetSwitch::cancelAnimations);

		lobbyOff->loadImage("Images/lobby_selected.png");
		lobbyOff->loadSprites(subRects);
		lobbyOff->setPosition(pos);
		lobbyOff->setDelay(1.2f);
		lobbyOff->setResetParameters(1.2f);
		lobbyOff->addActualSheet(2);
		lobbyOff->setCallback("click", lobbyOff, &WidgetSwitch::setUnvisible);
		lobbyOff->setCallback("click", lobbyOn, &WidgetSwitch::setVisible);
		lobbyOff->setCallback("click", lobbyOn, &WidgetSwitch::cancelAnimations);
	
		text->setText("");
		text->setPosition(sf::Vector2f(125.0f, static_cast<float>(58 + i * 54)));
		text->addActualSheet(2);
		text->setStyle(sf::Text::Bold, 25, "Images/charlie_dotted.ttf", 0, 0, 0);
		text->setDelay(1.2f);
		text->setResetParameters(1.2f);

		sheet->addWidgetToSheet(2, lobbyOn, &WidgetSwitch::resetWidget);
		sheet->addWidgetToSheet(2, lobbyOff, &WidgetSwitch::resetWidget);
		sheet->addWidgetToSheet(2, lobbyOn, &WidgetSwitch::setVisible);
		sheet->addWidgetToSheet(2, lobbyOff,  &WidgetSwitch::setUnvisible);
		sheet->addWidgetToSheet(2, text, &WidgetText::resetWidget);

		this->_lobbiesText.push_back(text);
		this->_lobbiesFrame.push_back(std::pair<WidgetSwitch *, WidgetSwitch *>(lobbyOn, lobbyOff));	
	}
	for (it = this->_lobbiesFrame.begin(); it != this->_lobbiesFrame.end(); ++it)
		for (it2 = this->_lobbiesFrame.begin(); it2 != this->_lobbiesFrame.end(); ++it2)
			if (it != it2)
			{
				(*it).first->setCallback("click", (*it2).second, &WidgetSwitch::setUnvisible);
				(*it).first->setCallback("click", (*it2).first, &WidgetSwitch::setVisible);
			}
	for (int i = 0; i <= 3; ++i)
	{
		lobbyOn = new WidgetSwitch;
		text = new WidgetText;

		pos.clear();
		pos.push_back(sf::Vector2f(116.0f, static_cast<float>(52 + i * 54)));
		pos.push_back(sf::Vector2f(static_cast<float>(WIN_X), static_cast<float>(WIN_Y)));
		lobbyOn->loadImage("Images/lobby_unselected.png");
		lobbyOn->loadSprites(subRects);
		lobbyOn->setPosition(pos);
		lobbyOn->setDelay(1.2f);
		lobbyOn->setResetParameters(1.2f);
		lobbyOn->setUnclickable();
		lobbyOn->addActualSheet(3);

		text->setText("");
		text->setPosition(sf::Vector2f(125.0f, static_cast<float>(58 + i * 54)));
		text->addActualSheet(3);
		text->setStyle(sf::Text::Bold, 25, "Images/charlie_dotted.ttf", 0, 0, 0);
		text->setDelay(1.2f);
		text->setResetParameters(1.2f);

		sheet->addWidgetToSheet(3, lobbyOn, &WidgetSwitch::resetWidget);
		sheet->addWidgetToSheet(3, text, &WidgetText::resetWidget);

		this->_playersText.push_back(text);
		this->_playersFrame.push_back(lobbyOn);	
	}

	for (int i = 0; i < 8; ++i)
	{
		text = new WidgetText;

		text->setText("");
		text->setPosition(sf::Vector2f(135.0f, static_cast<float>(345 + i * 30)));
		text->addActualSheet(3);
		text->setStyle(sf::Text::Bold, 25, "Images/charlie_dotted.ttf", 0, 0, 0);
		text->setDelay(1.2f);
		text->setResetParameters(1.2f);

		sheet->addWidgetToSheet(3, text, &WidgetText::resetWidget);

		this->_msgText.push_back(text);
	}
	subRects.clear();
	pos.clear();
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(0, 0), sf::Vector2i(1000, 800)));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(70, 25), 0.5f));
	pos.push_back(sf::Vector2f(-1000, 25));
	lobby_top_left->loadImage("Images/chat_top_left.png");
	lobby_top_left->loadSprites(subRects, 0, 255, 0);
	lobby_top_left->setPosition(pos);
	lobby_top_left->setAnimations(anims);
	lobby_top_left->addActualSheet(3);

	lobby_bot_left->loadImage("Images/chat_bot_left.png");
	lobby_bot_left->loadSprites(subRects, 0, 255, 0);
	lobby_bot_left->setPosition(pos);
	lobby_bot_left->setAnimations(anims);
	lobby_bot_left->addActualSheet(3);

	pos.clear();
	pos.push_back(sf::Vector2f(WIN_X + 1000, 25));
	lobby_bot_right->loadImage("Images/chat_bot_right.png");
	lobby_bot_right->loadSprites(subRects, 0, 255, 0);
	lobby_bot_right->setPosition(pos);
	lobby_bot_right->setAnimations(anims);
	lobby_bot_right->addActualSheet(3);

	lobby_top_right->loadImage("Images/chat_top_right.png");
	lobby_top_right->loadSprites(subRects, 0, 255, 0);
	lobby_top_right->setPosition(pos);
	lobby_top_right->setAnimations(anims);
	lobby_top_right->addActualSheet(3);

	pos.clear();
	pos.push_back(sf::Vector2f(70, 25));
	lobby_topleft->loadImage("Images/chat_topleft.png");
	lobby_topleft->loadSprites(subRects, 0, 255, 0);
	lobby_topleft->setPosition(pos);
	lobby_topleft->setTransitionTime(2.0, false);
	lobby_topleft->setDelay(0.5f);
	lobby_topleft->setResetParameters(0.5, 2.0);
	lobby_topleft->addActualSheet(3);

	lobby_botleft->loadImage("Images/chat_botleft.png");
	lobby_botleft->loadSprites(subRects, 0, 255, 0);
	lobby_botleft->setPosition(pos);
	lobby_botleft->setTransitionTime(2.0, false);
	lobby_botleft->setDelay(0.5f);
	lobby_botleft->setResetParameters(0.5, 2.0);
	lobby_botleft->addActualSheet(3);

	lobby_topright->loadImage("Images/chat_topright.png");
	lobby_topright->loadSprites(subRects, 0, 255, 0);
	lobby_topright->setPosition(pos);
	lobby_topright->setTransitionTime(2.0, false);
	lobby_topright->setDelay(0.5f);
	lobby_topright->setResetParameters(0.5, 2.0);
	lobby_topright->addActualSheet(3);

	lobby_botright->loadImage("Images/chat_botright.png");
	lobby_botright->loadSprites(subRects, 0, 255, 0);
	lobby_botright->setPosition(pos);
	lobby_botright->setTransitionTime(2.0, false);
	lobby_botright->setDelay(0.5f);
	lobby_botright->setResetParameters(0.5, 2.0);
	lobby_botright->addActualSheet(3);

	juda->loadImage("Images/chat_bozza.png");
	juda->loadSprites(subRects, 0, 255, 0);
	juda->setPosition(pos);
	juda->setTransitionTime(2.0, false);
	juda->setDelay(0.5f);
	juda->setResetParameters(0.5, 2.0);
	juda->addActualSheet(3);

	anims.clear();
	pos.clear();
	subRects.clear();
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(0, 0), sf::Vector2i(200, 50)));
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(200, 0), sf::Vector2i(400, 50)));
	pos.push_back(sf::Vector2f(WIN_X + 200, 478));
	pos.push_back(sf::Vector2f(WIN_X, WIN_Y));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(WIN_X - 305, 478), 0.5f));
	leave->loadImage("Images/leave.png");
	leave->loadSprites(subRects);
	leave->setPosition(pos);
	leave->setAnimations(anims);
	leave->addActualSheet(3);
	leave->setDestinationSheet(2);
	leave->setCallback("animationFinished", leave, &WidgetButton::setClickable);
	leave->setCallback("click", this, &GameMenu::leaveLobby);
	leave->setCallback("click", this, &GameMenu::clearLobbies);
	leave->setCallback("click", this->_parser, &Parser::addNBL);
	leave->setCallback("click", this->_parser, &Parser::addNBP);

	anims.clear();
	pos.clear();
	pos.push_back(sf::Vector2f(WIN_X + 200, 422));
	pos.push_back(sf::Vector2f(WIN_X, WIN_Y));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(WIN_X - 305, 422), 0.5f));
	start->loadImage("Images/start.png");
	start->loadSprites(subRects);
	start->setPosition(pos);
	start->setAnimations(anims);
	start->addActualSheet(3);
	start->setCallback("animationFinished", start, &WidgetButton::setClickable);
	start->setCallback("click", this, &GameMenu::startGame);

	anims.clear();
	pos.clear();
	pos.push_back(sf::Vector2f(WIN_X + 200, 585));
	pos.push_back(sf::Vector2f(WIN_X, WIN_Y));
	anims.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(WIN_X - 305, 585), 0.5f));
	send->loadImage("Images/send.png");
	send->loadSprites(subRects);
	send->setPosition(pos);
	send->setAnimations(anims);
	send->addActualSheet(3);
	send->setCallback("click", this, &GameMenu::sendMsg);
	send->setCallback("animationFinished", send, &WidgetButton::setClickable);

	subRects.clear();
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(0, 0), sf::Vector2i(537, 30)));
	subRects.push_back(std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(0, 0), sf::Vector2i(536, 30)));
	pos.clear();
	pos.push_back(sf::Vector2f(121, 610));
	pos.push_back(sf::Vector2f(WIN_X, WIN_Y));
	input->loadImage("Images/chat_input.png");
	input->loadSprites(subRects);
	input->setPosition(pos);
	input->setDelay(1.2f);
	input->setResetParameters(1.2f);
	input->addActualSheet(3);
	input->setCallback("click", win, &RenderWindow::switchMsg);
	input->setCallback("click", this->_typingBar, &WidgetTypingBar::switchActivate);

	this->_inputMsg = new WidgetText;
	this->_inputMsg->setText("");
	this->_inputMsg->setPosition(sf::Vector2f(128, 609));
	this->_inputMsg->addActualSheet(3);
	this->_inputMsg->setStyle(sf::Text::Bold, 22, "Images/charlie_dotted.ttf", 0, 0, 0);
	this->_inputMsg->setDelay(1.2f);
	this->_inputMsg->setResetParameters(1.2f);
	sheet->addWidgetToSheet(3, lobby_topright, &WidgetImage::resetWidget);
	sheet->addWidgetToSheet(3, lobby_botright, &WidgetImage::resetWidget);
	sheet->addWidgetToSheet(3, lobby_botleft, &WidgetImage::resetWidget);
	sheet->addWidgetToSheet(3, lobby_topleft, &WidgetImage::resetWidget);
	sheet->addWidgetToSheet(3, lobby_top_right, &WidgetImage::resetWidget);
	sheet->addWidgetToSheet(3, lobby_bot_right, &WidgetImage::resetWidget);
	sheet->addWidgetToSheet(3, lobby_bot_left, &WidgetImage::resetWidget);
	sheet->addWidgetToSheet(3, lobby_top_left, &WidgetImage::resetWidget);
	sheet->addWidgetToSheet(3, juda, &WidgetImage::resetWidget);
	sheet->addWidgetToSheet(3, start, &WidgetButton::resetWidget);
	sheet->addWidgetToSheet(3, start, &WidgetButton::setUnclickable);
	sheet->addWidgetToSheet(3, leave, &WidgetButton::resetWidget);
	sheet->addWidgetToSheet(3, leave, &WidgetButton::setUnclickable);
	sheet->addWidgetToSheet(3, send, &WidgetButton::resetWidget);
	sheet->addWidgetToSheet(3, send, &WidgetButton::setUnclickable);
	sheet->addWidgetToSheet(3, input, &WidgetSwitch::resetWidget);
	sheet->addWidgetToSheet(3, this->_inputMsg, &WidgetText::resetWidget);

	this->_widgets.push_back(lobby_topright);
	this->_widgets.push_back(lobby_botright);
	this->_widgets.push_back(lobby_botleft);
	this->_widgets.push_back(lobby_topleft);
	this->_widgets.push_back(lobby_top_right);
	this->_widgets.push_back(lobby_bot_right);
	this->_widgets.push_back(lobby_bot_left);
	this->_widgets.push_back(lobby_top_left);
	this->_widgets.push_back(start);
	this->_widgets.push_back(leave);
	this->_widgets.push_back(send);
	this->_widgets.push_back(input);
	this->_widgets.push_back(this->_inputMsg);
	this->_widgets.push_back(juda);
}

void		GameMenu::initParser(Parser &parser)
{
	parser.addCallback(CMD_PNB, boost::bind(&GameMenu::setPlayerId, this, _1));
	parser.addCallback(CMD_NBP, boost::bind(&GameMenu::setTotalPlayers, this, _1));
	parser.addCallback(CMD_NBL, boost::bind(&GameMenu::addLobby, this, _1));
	parser.addCallback(CMD_JNL, boost::bind(&GameMenu::joinLobby, this, _1));
	parser.addCallback(CMD_CRL, boost::bind(&GameMenu::joinLobby, this, _1));
	parser.addCallback(CMD_CRL, boost::bind(&GameMenu::setLobbyId, this, _1));
	parser.addCallback(CMD_PLJ, boost::bind(&GameMenu::addPlayer, this, _1));
	parser.addCallback(CMD_STL, boost::bind(&GameMenu::setFinished, this, _1));
	parser.addCallback(CMD_LVL, boost::bind(&GameMenu::leaveLobby, this, _1));
	parser.addCallback(CMD_MSG, boost::bind(&GameMenu::addMsg, this, _1));
	this->_parser = &parser;
}

int		GameMenu::loadResources(RenderWindow *win)
{
	try {
		this->_sheets.setSheetPointer(&(this->_sheetNb));
		this->_sheets.setActualSheet(0);
		this->_win = win;
		this->loadImages();
		this->loadButtons(win);
		this->refreshLobbies();
	}
	catch (RuntimeException &e) {
		this->_exception = e;
		this->_exceptionOccured = true;
		return (-1);
	}
	return (0);
}

void		GameMenu::exception()
{
	if (this->_exceptionOccured)
		throw this->_exception;
}

void		GameMenu::askNbPlayers()
{
}

void		GameMenu::refreshMsg()
{
	std::list<std::pair<unsigned char, std::string> >::iterator		it;
	std::list<std::pair<unsigned char, std::string> >::iterator		it3;
	std::list<WidgetText *>::iterator								it2 = this->_msgText.begin();
	std::string			final;

	for (it = this->_msgList.begin(); it != this->_msgList.end(); ++it)
	{
		for (it3 = this->_playersList.begin(); it3 != this->_playersList.end(); ++it3)
			if ((*it3).first == (*it).first)
				break;
		if (it3 != this->_playersList.end() && it2 != this->_msgText.end())
		{
			final = (*it3).second;
			final += " : ";
			final += (*it).second;
			(*it2)->setText(final);
			++it2;
		}
	}
	for (; it2 != this->_msgText.end(); ++it2)
		(*it2)->setText("");
}

void		GameMenu::refreshPlayers()
{
	std::list<std::pair<unsigned char, std::string> >::iterator		it;
	std::list<WidgetText *>::iterator								it2 = this->_playersText.begin();
	std::list<WidgetSwitch *>::iterator								it3 = this->_playersFrame.begin();
	std::string														final;

	for (it = this->_playersList.begin(); it != this->_playersList.end(); ++it)
		if (it2 != this->_playersText.end() && it3 != this->_playersFrame.end())
		{
			final = (*it).second;
			if (it2 == this->_playersText.begin())
				final += " (Host)";
			(*it3)->setVisible();
			(*it2)->setText(final);
			(*it3)->clearSheets();
			(*it3)->addActualSheet(3);
			(*it3)->setVisible();
			++it2;
			++it3;
		}
	for (; it3 != this->_playersFrame.end(); ++it3)
		(*it3)->clearSheets();
	for (; it2 != this->_playersText.end(); ++ it2)
		(*it2)->setText("");
}

void		GameMenu::refreshLobbies()
{
	std::list<std::pair<unsigned char, unsigned char> >::iterator	it;
	std::list<WidgetText *>::iterator								it2 = this->_lobbiesText.begin();
	std::list<std::pair<WidgetSwitch *, WidgetSwitch *> >::iterator	it3 = this->_lobbiesFrame.begin();
	std::stringstream												ss;
	std::stringstream												ss2;
	std::string														final;

	for (it = this->_lobbiesList.begin(); it != this->_lobbiesList.end(); ++it)
		if (it2 != this->_lobbiesText.end() && it3 != this->_lobbiesFrame.end())
		{
			ss << static_cast<int>((*it).first);
			ss2 << static_cast<int>((*it).second);
			final = ((*it).first < 100) ? (((*it).first < 10) ? ("-- Lobby #00") : ("-- Lobby #0")) : ("-- Lobby #");
			final += ss.str();
			final += " --                                                                      -- ";
			final += ss2.str();
			final += "/4 --";
			(*it3).second->setVisible();
			(*it3).first->setVisible();
			(*it2)->setText(final);
			(*it3).first->clearSheets();
			(*it3).second->clearSheets();
			(*it3).first->addActualSheet(2);
			(*it3).second->addActualSheet(2);
			(*it3).second->setUnvisible();
			(*it3).first->setVisible();
			ss.str("");
			ss2.str("");
			++it2;
			++it3;
		}
	for(; it3 != this->_lobbiesFrame.end(); ++it3)
	{
		(*it3).first->clearSheets();
		(*it3).second->clearSheets();
	}
	for (; it2 != this->_lobbiesText.end(); ++it2)
		(*it2)->setText("");
}

boost::any	GameMenu::setLobbyId(std::list<boost::any> args)
{
	if (boost::any_cast<unsigned char>(args.front()) != 0)
		this->_lobbyId = boost::any_cast<unsigned char>(args.front());
	return (0);
}

boost::any	GameMenu::joinLobby(std::list<boost::any> args)
{
	if (boost::any_cast<unsigned char>(args.front()) != 0)
		this->_sheets.setActualSheet(3);
	else
		throw MinorException("[GameMenu::joinLobby]", "Can't join lobby");
	return (0);
}

boost::any	GameMenu::leaveLobby(std::list<boost::any> args)
{
	std::list<std::pair<unsigned char, std::string> >::iterator it;

	if (boost::any_cast<unsigned char>(args.front()) == this->_playerId)
	{
		this->_sheets.setActualSheet(2);
		this->clearPlayers();
		this->clearLobbies();
		this->refreshLobbies();
	}
	else
		for (it = this->_playersList.begin(); it != this->_playersList.end(); ++it)
			if ((*it).first == boost::any_cast<unsigned char>(args.front()))
			{
				this->_playersList.erase(it);
				break;
			}
	this->refreshPlayers();
	return (0);
}

boost::any	GameMenu::setPlayerId(std::list<boost::any> args)
{
	this->_playerId = boost::any_cast<unsigned char>(args.front());
	return (0);
}

boost::any	GameMenu::addMsg(std::list<boost::any> args)
{
	if (this->_msgList.size() == 8)
		this->_msgList.pop_front();
	this->_msgList.push_back(std::pair<unsigned char, std::string>(boost::any_cast<unsigned char>(args.front()), boost::any_cast<std::string>(args.back())));
	this->refreshMsg();
	return (0);
}

boost::any	GameMenu::setTotalPlayers(std::list<boost::any> args)
{
	std::stringstream	ss;

	ss << "Online Players : ";
	ss << static_cast<int>(boost::any_cast<unsigned char>(args.front()));
	this->_playersLabel->setText(ss.str());
	return (0);
}

boost::any	GameMenu::addLobby(std::list<boost::any> args)
{
	std::list<std::pair<unsigned char, unsigned char> >::iterator it;
	std::stringstream	ss;
	bool	found = false;

	for (it = this->_lobbiesList.begin(); it != this->_lobbiesList.end(); ++it)
		if ((*it).first == boost::any_cast<unsigned char>(args.front()))
		{
			found = true;
			(*it).second = boost::any_cast<unsigned char>(args.back());
		}
	if (!found)
	{
		this->_lobbiesList.push_back(std::pair<unsigned char, unsigned char>(boost::any_cast<unsigned char>(args.front()), boost::any_cast<unsigned char>(args.back())));
		this->refreshLobbies();
	}
	this->_totalLobbies = this->_lobbiesList.size();
	ss << "Open lobbies : ";
	ss << this->_totalLobbies;
	this->_lobbiesLabel->setText(ss.str());
	return (0);
}

boost::any	GameMenu::addPlayer(std::list<boost::any> args)
{
	std::cout << "Added Player ";
	this->_playersList.push_back(std::pair<unsigned char, std::string>(boost::any_cast<unsigned char>(args.front()), boost::any_cast<std::string>(args.back())));
	this->refreshPlayers();
	std::cout << "- Size : " << this->_playersList.size() << std::endl;
	return (0);
}

void	GameMenu::clearLobbies()
{
	this->_lobbiesList.clear();
	this->refreshLobbies();
	this->_lobbiesLabel->setText("Open lobbies : 0");
}

void	GameMenu::clearPlayers()
{
	this->_playersList.clear();
	this->refreshPlayers();
}

void	GameMenu::startGame()
{
	this->_parser->addSTL(this->_lobbyId);
}

void		GameMenu::sendMsg()
{
	if (this->_win->getMsg().compare("") != 0)
		this->_parser->addMSG(this->_playerId, this->_lobbyId, this->_win->getMsg());
	this->_win->clearMsg();
}

void		GameMenu::rstClock()
{
	this->_clock.restart();
}

void		GameMenu::joinLobby()
{
	bool	found = false;
	int		i = 0, u = 0;
	std::list<std::pair<WidgetSwitch *, WidgetSwitch *> >::iterator it;
	std::list<std::pair<unsigned char, unsigned char> >::iterator it2;

	for (it = this->_lobbiesFrame.begin(); it != this->_lobbiesFrame.end(); ++it)
		if ((*it).second->isSelected())
		{
			found = true;
			break;
			++i;
		}
	if (found)
	{
		for (it2 = this->_lobbiesList.begin(); it2 != this->_lobbiesList.end(); ++it2)
		{
			if (i == u)
			{
				this->_lobbyId = (*it2).first;
				break;
			}
			++u;
		}
		this->_parser->addJNL(this->_playerId, this->_lobbyId);
	}
	this->_msgList.clear();
	this->refreshMsg();
}

void		GameMenu::createLobby()
{
	this->_parser->addCRL(this->_playerId);
	this->_msgList.clear();
	this->refreshMsg();
}

void		GameMenu::setNickname()
{
	this->_parser->addNMP(this->_playerId, this->_win->getNickname());
}

void		GameMenu::leaveLobby()
{
	this->_parser->addLVL(this->_playerId, this->_lobbyId);
}

void		GameMenu::checkInputs(RenderWindow &win)
{
	//const sf::Input& input = win.getInput();

/*	if (input.IsKeyDown(sf::Key::Escape))
	{
		std::list<AWidget *>::iterator		it;
		std::list<std::pair<WidgetSwitch *, WidgetSwitch *> >::iterator		it2;
		std::list<WidgetText *>::iterator									it3;
		std::list<WidgetSwitch *>::iterator									it4;

		if (this->_sheetSkipped && (this->_sheetSkippedval != this->_sheetNb))
			this->_sheetSkipped = false;
		if (!(this->_sheetSkipped))
		{
			for (it = this->_widgets.begin(); it != this->_widgets.end(); ++it)
				(*it)->skipAnimations();
			for (it2 = this->_lobbiesFrame.begin(); it2 != this->_lobbiesFrame.end(); ++it2)
			{
				(*it2).first->skipAnimations();
				(*it2).second->skipAnimations();
			}
			for (it3 = this->_lobbiesText.begin(); it3 != this->_lobbiesText.end(); ++it3)
				(*it3)->skipAnimations();
			for (it4 = this->_playersFrame.begin(); it4 != this->_playersFrame.end(); ++it4)
				(*it4)->skipAnimations();
			for (it3 = this->_playersText.begin(); it3 != this->_playersText.end(); ++it3)
				(*it3)->skipAnimations();
			for (it3 = this->_msgText.begin(); it3 != this->_msgText.end(); ++it3)
				(*it3)->skipAnimations();
			this->_typingBar->skipAnimations();
			this->_sheetSkipped = true;
			this->_sheetSkippedval = this->_sheetNb;
		}
	}*/
	/*if (!(input.IsKeyDown(sf::Key::Return)))
		this->_antiSpam = false;
	if (input.IsKeyDown(sf::Key::Return) && !(this->_antiSpam))
	{
		if (win.msgActive())
		{
			this->sendMsg();
			this->_antiSpam = true;
		}
		if (win.nickActive())
		{
			win.switchNick();
			this->_typingBar->switchActivate();
			this->setNickname();
		}

	}*/
}

void		GameMenu::update(RenderWindow &window)
{
	float	elapsed = this->_clock.getElapsedTime().asSeconds();
	std::list<AWidget *>::iterator		it;
	std::list<std::pair<WidgetSwitch *, WidgetSwitch *> >::iterator		it2;
	std::list<WidgetText *>::iterator									it3;
	std::list<WidgetSwitch *>::iterator									it4;
	sf::FloatRect		rect;
	
	this->rstClock();

	(window.msgActive()) ? (rect = this->_inputMsg->getRect()) : (rect = this->_input->getRect());
	this->_input->setText(window.getNickname());
	this->_inputMsg->setText(window.getMsg());
	this->_typingBar->setPosition(sf::Vector2f(rect.left + rect.width, rect.top));
	this->checkInputs(window);
	
	for (it = this->_widgets.begin(); it != this->_widgets.end(); ++it)
		(*it)->update(elapsed, window, this->_sheetNb);
	for (it2 = this->_lobbiesFrame.begin(); it2 != this->_lobbiesFrame.end(); ++it2)
	{
		(*it2).first->update(elapsed, window, this->_sheetNb);
		(*it2).second->update(elapsed, window, this->_sheetNb);
	}
	for (it3 = this->_lobbiesText.begin(); it3 != this->_lobbiesText.end(); ++it3)
		(*it3)->update(elapsed, window, this->_sheetNb);
	for (it4 = this->_playersFrame.begin(); it4 != this->_playersFrame.end(); ++it4)
		(*it4)->update(elapsed, window, this->_sheetNb);
	for (it3 = this->_playersText.begin(); it3 != this->_playersText.end(); ++it3)
		(*it3)->update(elapsed, window, this->_sheetNb);
	for (it3 = this->_msgText.begin(); it3 != this->_msgText.end(); ++it3)
		(*it3)->update(elapsed, window, this->_sheetNb);
	this->_typingBar->update(elapsed, window, (window.msgActive()) ? (this->_inputMsg->getSize()) : (this->_input->getSize()));
}

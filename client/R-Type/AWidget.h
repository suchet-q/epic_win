#pragma once
#include	<vector>
#include	<iostream>
#include	"Sprite.h"
#include	"Callback.hpp"
#include	"Sheets.h"

class AWidget
{
protected:
	std::map<std::string, std::list<Callback *>>		_callback;
	std::vector<Sprite *>	_sprites;
	std::string				_img;
	float				_delay;
	float				_transition;
	float				_timeToLive;
	bool				_useDelay;
	bool				_useTransition;
	bool				_transitionFull;
	bool				_useTimeToLive;
	std::list<int>		_actualSheets;
public:
	AWidget(void);
	virtual ~AWidget(void);
	
	
	virtual void	loadSprites(std::list<std::pair<sf::Vector2f, sf::Vector2f>> &) = 0;
	virtual void	setPosition(std::list<sf::Vector2f> &) = 0;
	virtual void	setAnimations(std::list<std::pair<sf::Vector2f, float>> &) = 0;
	virtual void	update(float, RenderWindow &, int) = 0;

	virtual void	loadImage(const std::string &filename);
	virtual void	setTransitionTime(float, bool);
	virtual void	setDelay(float);
	virtual void	setTimeToLive(float);
	virtual void	addActualSheet(int);
	virtual void	triggerCallback(const std::string &eventName);
	template <typename T>
	void	setCallback(std::string const &eventName, T *ref, void (T::*method)()) {
		this->_callback[eventName].push_back(new CallbackT<T>(ref, method));
	}
};


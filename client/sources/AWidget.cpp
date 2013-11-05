#include "AWidget.h"


AWidget::AWidget(void)
{
	this->_useDelay = false;
	this->_useTransition = false;
	this->_useTimeToLive = false;
	this->_transitionFull = false;
}

AWidget::~AWidget(void)
{
	if (!(this->_sprites.empty()))
		for (int i = 0; i < this->_sprites.size(); ++i)
			delete this->_sprites[i];
}

void		AWidget::loadImage(const std::string &filename)
{
	this->_img = filename;
}

void		AWidget::setTransitionTime(float time, bool full)
{
	this->_useTransition = true;
	this->_transitionFull = full;
	this->_transition = time;
}

void		AWidget::setDelay(float delay)
{
	this->_useDelay = true;
	this->_delay = delay;
}

void		AWidget::setTimeToLive(float ttl)
{
	this->_useTimeToLive = true;
	this->_timeToLive = ttl;
}

void		AWidget::triggerCallback(const std::string &eventName)
{
	std::list<Callback *>::iterator	it;

	for (it = this->_callback[eventName].begin(); it != this->_callback[eventName].end(); ++it)
		(*it)->triggerCallback();
}

void		AWidget::addActualSheet(int sheet)
{
	this->_actualSheets.push_back(sheet);
}
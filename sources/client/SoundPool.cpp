#include "SoundPool.h"

SoundPool		*SoundPool::_instance = NULL;

SoundPool::SoundPool(void)
{
}


SoundPool::~SoundPool(void)
{
}

void		SoundPool::initialize()
{
	this->_soundOn = true;
	this->_musicOn = true;

	this->_soundsBuffer["ButtonHover"].loadFromFile("Sounds/ButtonHover.ogg");
	this->_soundsBuffer["ButtonClicked"].loadFromFile("Sounds/ButtonClicked.ogg");
}

void		SoundPool::playSound(const std::string &name, const std::string &bufferName, float volume, bool loop)
{
	if (this->_soundOn)
	{
		this->_sounds[name].setBuffer(this->_soundsBuffer[bufferName]);
		this->_sounds[name].setVolume(volume);
		this->_sounds[name].setLoop(loop);
		this->_sounds[name].play();
	}
}

void		SoundPool::enableSound()
{
	this->_soundOn = true;
}

void		SoundPool::disableSound()
{
	this->_soundOn = false;
}

void		SoundPool::enableMusic()
{
	this->_musicOn = true;
}

void		SoundPool::disableMusic()
{
	this->_musicOn = false;
}

void		SoundPool::buttonHover()
{
	this->playSound("ButtonHover", "ButtonHover");
}

void		SoundPool::buttonClicked()
{
	this->playSound("ButtonClicked", "ButtonClicked");
}
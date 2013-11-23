#include "SoundPool.h"

SoundPool		*SoundPool::_instance = NULL;

SoundPool::SoundPool(void)
{
}


SoundPool::~SoundPool(void)
{
}

bool		SoundPool::initialize()
{
	this->_soundOn = true;
	this->_musicOn = true;

	//this->_soundsBuffer["ButtonHover"].loadFromFile("Sounds/ButtonHover.ogg");
	//this->_soundsBuffer["ButtonClicked"].loadFromFile("Sounds/ButtonClicked.ogg");
	if (!this->_musicMenu.openFromFile("Music/03-menu.ogg"))
	  return false;
	if (!this->_musicLvlOne.openFromFile("Music/01-opening.ogg"))
	  return false;
	// if (!this->_musicLoose.OpenFromFile("Music/EndOfGame.ogg"))
	//   return;
	if (!this->_musicMort.loadFromFile("Music/21-game-over.ogg"))
	  return false;
	this->_Dead.setBuffer(_musicMort);
	return true;
}

void		SoundPool::playSound(const std::string &name, const std::string &bufferName, float volume, bool loop)
{
	if (this->_soundOn)
	{
		/*this->_sounds[name].setBuffer(this->_soundsBuffer[bufferName]);
		this->_sounds[name].setVolume(volume);
		this->_sounds[name].setLoop(loop);
		this->_sounds[name].play();*/
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

void			SoundPool::loopMenu()
{
  this->_musicMenu.setLoop(true);
}

void			SoundPool::loopLvlOne()
{
  this->_musicLvlOne.setLoop(true);
}

// void			SoundPool::loopLoose()
// {
//   this->_musicLoose.setLoop(true);
// }

void			SoundPool::playDead()
{
  this->_Dead.play();
}

void			SoundPool::pauseDead()
{
  this->_Dead.pause();
}

void			SoundPool::stopDead()
{
  this->_Dead.stop();
}

void			SoundPool::playMenu()
{
  this->_musicMenu.play();
}

void			SoundPool::pauseMenu()
{
  this->_musicMenu.pause();
}

void			SoundPool::stopMenu()
{
  this->_musicMenu.stop();
}

void			SoundPool::playLvlOne()
{
  this->_musicLvlOne.play();
}

void			SoundPool::pauseLvlOne()
{
  this->_musicLvlOne.pause();
}

void			SoundPool::stopLvlOne()
{
  this->_musicLvlOne.stop();
}

// void			SoundPool::playLoose()
// {
//   this->_SoundPoolLoose.Play();
// }

// void			SoundPool::pauseLoose()
// {
//   this->_SoundPoolLoose.Pause();
// }

// void			SoundPool::stopLoose()
// {
//   this->_SoundPoolLoose.Stop();
// }

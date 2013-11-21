/*#include "Music.h"

Music::Music()
{
if (!this->_musicMenu.OpenFromFile("Music/03-menu.ogg"))
    return;
  if (!this->_musicLvlOne.OpenFromFile("Music/01-opening.ogg"))
    return;
  if (!this->_musicLoose.OpenFromFile("Music/EndOfGame.ogg"))
    return;
  if (!this->_musicMort.LoadFromFile("Music/21-game-over.ogg"))
    return;
  this->_Dead.SetBuffer(_musicMort);
}

Music::~Music()
{
  
}

void			Music::loopMenu()
{
  this->_musicMenu.SetLoop(true);
}

void			Music::loopLvlOne()
{
  this->_musicLvlOne.SetLoop(true);
}

void			Music::loopLoose()
{
  this->_musicLoose.SetLoop(true);
}

void			Music::playDead()
{
  this->_Dead.Play();
}

void			Music::pauseDead()
{
  this->_Dead.Pause();
}

void			Music::stopDead()
{
  this->_Dead.Stop();
}

void			Music::playMenu()
{
  this->_musicMenu.Play();
}

void			Music::pauseMenu()
{
  this->_musicMenu.Pause();
}

void			Music::stopMenu()
{
  this->_musicMenu.Stop();
}

void			Music::playLvlOne()
{
  this->_musicLvlOne.Play();
}

void			Music::pauseLvlOne()
{
  this->_musicLvlOne.Pause();
}

void			Music::stopLvlOne()
{
  this->_musicLvlOne.Stop();
}

void			Music::playLoose()
{
  this->_musicLoose.Play();
}

void			Music::pauseLoose()
{
  this->_musicLoose.Pause();
}

void			Music::stopLoose()
{
  this->_musicLoose.Stop();
}
*/
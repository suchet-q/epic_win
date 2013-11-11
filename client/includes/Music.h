# pragma once

# include <SFML/Audio.hpp>

class		Music
{
 private:
  sf::Music		_musicMenu;
  sf::Music		_musicLvlOne;
  sf::Music		_musicLoose;
  sf::SoundBuffer	_musicMort;
  sf::SoundBuffer	_musicBonus;
  sf::SoundBuffer	_musicBroken;
  sf::SoundBuffer	_musicSelect;
  sf::SoundBuffer	_musicWin;
  sf::SoundBuffer	_musicExplosion;
  sf::Sound		_Dead;
  sf::Sound	        _Bonus;
  sf::Sound	        _Broken;
  sf::Sound	        _Select;
  sf::Sound		_Win;
  sf::Sound		_Explosion;

  public:
  Music();
  ~Music();
  void          playDead(); 
  void		pauseDead();
  void		stopDead();
  void		playMenu();
  void		pauseMenu();
  void		stopMenu();
  void		playLvlOne();
  void		pauseLvlOne();
  void		stopLvlOne();
  void		playLoose();
  void		pauseLoose();
  void		stopLoose();
  void		loopMenu();
  void		loopLvlOne();
  void		loopLoose();
};

#pragma once

#include	<map>
#include	<SFML/Audio.hpp>
#include	<iostream>
#include	"RuntimeException.h"

class SoundPool
{
	std::map<std::string, sf::SoundBuffer>	_soundsBuffer;
	std::map<std::string, sf::Sound>		_sounds;
	bool									_soundOn;
	bool									_musicOn;
	static SoundPool						*_instance;

	SoundPool(void);
	~SoundPool(void);

	bool									initialize();
	sf::Music		_musicMenu;
	sf::Music		_musicLvlOne;
	/* sf::Music		_musicLoose; */
	sf::SoundBuffer		_musicMort;
	sf::Sound		_Dead;


public:

	static SoundPool *getInstance() {
		if (_instance == NULL)
		{
			_instance = new SoundPool();
			_instance->initialize();
		}
		return (_instance);
	}
	
	void		playSound(const std::string &, const std::string &, float = 100.0, bool = false);
	void		buttonHover();
	void		buttonClicked();
	void		enableSound();
	void		disableSound();
	void		enableMusic();
	void		disableMusic();

	void		playDead(); 
	void		pauseDead();
	void		stopDead();
	void		playMenu();
	void		pauseMenu();
	void		stopMenu();
	void		playLvlOne();
	void		pauseLvlOne();
	void		stopLvlOne();
	/* void		playLoose(); */
	/* void		pauseLoose(); */
	/* void		stopLoose(); */
	void		loopMenu();
	void		loopLvlOne();
	/* void		loopLoose(); */
};

#pragma once

#include	<map>
#include	<SFML/Audio.hpp>
#include	<iostream>

class SoundPool
{
	std::map<std::string, sf::SoundBuffer>	_soundsBuffer;
	std::map<std::string, sf::Sound>		_sounds;
	bool									_soundOn;
	bool									_musicOn;
	static SoundPool						*_instance;

	SoundPool(void);
	~SoundPool(void);
	void									initialize();
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
};
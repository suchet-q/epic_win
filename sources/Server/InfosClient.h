#pragma once
#include	<iostream>
#include	<string>

enum		Weapons
{
	MISSIL,
	LASER
};

class		InfosClient
{
private:
	int		_life;
	Weapons	_weapon;
	bool	_bonus;
	int		_score;
	int		_hightScore;
public:
	InfosClient();
	~InfosClient();
	void	setLife(int);
	void	setWeapon(Weapons);
	void	setBonus(bool);
	void	setScore(int);
	void	setHightScore(int);
	int		getLife();
	Weapons	getWeapon();
	bool	getBonus();
	int		getScore();
	int		getHightScore();
};
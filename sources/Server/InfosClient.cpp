#include	"InfosClient.h"

InfosClient::InfosClient() {}

InfosClient::~InfosClient() {}

void	InfosClient::setLife(int life)
{
	this->_life = life;
}

void	InfosClient::setWeapon(Weapons weapon)
{
	this->_weapon = weapon;
}

void	InfosClient::setBonus(bool bonus)
{
	this->_bonus = bonus;
}

void	InfosClient::setScore(int score)
{
	this->_score = score;
}

void	InfosClient::setHightScore(int hightscore)
{
	this->_hightScore = hightscore;
}

int		InfosClient::getLife()
{
	return (this->_life);
}

Weapons	InfosClient::getWeapon()
{
	return (this->_weapon);
}

bool	InfosClient::getBonus()
{
	return (this->_bonus);
}

int		InfosClient::getScore()
{
	return (this->_score);
}

int		InfosClient::getHightScore()
{
	return (this->_hightScore);
}
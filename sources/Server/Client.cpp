#include "Client.h"


Client::Client()
{
	this->_infosClient.life = 0;
	this->_infosClient.host = false;
	for (int i = 0; i <= 16; ++i)
		this->_infosClient.nick_name[i] = '\0';
	this->_infosClient.weapon = MISSIL;
	this->_infosClient.bonus = false;
	this->_infosClient.score = 0;
	this->_infosClient.hightScore = 0;
}


Client::~Client()
{
}

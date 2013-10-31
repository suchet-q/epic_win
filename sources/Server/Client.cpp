#include "Client.h"


Client::Client(int id)
{
	this->_id = id;
	this->_host = false;
	this->_infosClient.life = 0;
	this->_infosClient.weapon = MISSIL;
	this->_infosClient.bonus = false;
	this->_infosClient.score = 0;
	this->_infosClient.hightScore = 0;
	for (int i = 0; i <= 16; ++i)
		this->_nickName[i] = '\0';
}


Client::~Client() {}

int		Client::getID()
{
	return (this->_id);
}

bool	Client::getHost()
{
	return (this->_host);
}

void	Client::setHost(bool host)
{
	this->_host = host;
}

char const	&Client::getNickName()
{
	return (*this->_nickName);
}

bool	Client::setNickName(const char *nickName)
{
	if (strlen(nickName) > 16)
		return (false);
	for (unsigned int i = 0; i <= strlen(nickName); ++i)
		this->_nickName[i] = nickName[i];
	return (true);
}

t_infos_game	&Client::getInfosClient()
{
	return (this->_infosClient);
}
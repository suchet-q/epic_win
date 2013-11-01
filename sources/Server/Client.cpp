#include "Client.h"

Client::Client(int id, MetaSocket<> *socket)
{
  this->_socket = socket;
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

void			Client::addMsgSend(void *command, int size)
{
	std::pair<void *, unsigned int> *tmp = new std::pair<void *, unsigned int>;

	tmp->first = command;
	tmp->second = size;
	this->_writeBuffer.push_back(*tmp);
}

MetaSocket<>	*Client::getSocket() const
{
	return (this->_socket);
}

std::list<std::pair<void *, unsigned int> >	*Client::getWriteBuffer() const
{
	return (const_cast<std::list<std::pair<void *, unsigned int> > *>(&this->_writeBuffer));
}

std::list<std::pair<void *, unsigned int> >	*Client::getReadBuffer() const
{
	return (const_cast<std::list<std::pair<void *, unsigned int> > *>(&this->_readBuffer));
}

int		Client::sendCommand()
{
	if (this->_socket->Send(this->_writeBuffer.front().first,
		    this->_writeBuffer.front().second) <= 0)
		return (-1);
	this->_writeBuffer.pop_front();
	return (0);
}

int		Client::recvCommand()
{
	std::pair<void *, unsigned int> *tmp = new std::pair<void *, unsigned int>;
	int width = 0;

	if (width = this->_socket->Recv(tmp->first, 300) <= 0)
		return (-1);
	tmp->second = width;
	this->_readBuffer.push_back(*tmp);
	return (0);
}

int		Client::getID() const
{
	return (this->_id);
}

bool	Client::getHost() const
{
	return (this->_host);
}

void	Client::setHost(bool host)
{
	this->_host = host;
}

char const	&Client::getNickName() const
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

t_infos_game	*Client::getInfosClient() const
{
	return (const_cast<t_infos_game *>(&this->_infosClient));
}

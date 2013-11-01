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

oMetaSocket<>	*Client::getSocket() {
  return _socket;
}

std::list<std::pair<void *, unsigned int> >	&Client::getWriteBuffer() {
  return _writeBuffer;
}

std::list<std::pair<void *, unsigned int> >	&Client::getReadBuffer() {
 return _readBuffer;
}

int		Client::sendCommand()
{
  if (_socket->Send(_writeBuffer.back().first(),
		    _writeBuffer.back().second()) <= 0)
    return (-1);
  _writeBuffer.pop_back();
  return (0);
}

int		Client::recvCommand()
{
  if (_socket->Recv(_readBuffer.back().first(),
		    _readBuffer.back().second()) <= 0)
    return (-1);
  _readBuffer.pop_back();
  return (0);
}

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

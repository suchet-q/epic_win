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
  for (int i = 0; i < GREATEST_COMMAND_SIZE; ++i)
    this->_buffer.cmd[i] = -1;
  this->_buffer.size = 0;
}

Client::~Client() {}

MetaSocket<>	*Client::getSocket() const
{
  return (this->_socket);
}

std::list<t_cmd>	*Client::getWriteBuffer() const
{
  return (const_cast<std::list<t_cmd> *>(&this->_writeBuffer));
}

std::list<t_cmd>	*Client::getReadBuffer() const
{
  return (const_cast<std::list<t_cmd> *>(&this->_readBuffer));
}

void		Client::parseCommand(void *buffer, unsigned int size, std::map<char, unsigned int> &cmdSize)
{
  char		*buff = reinterpret_cast<char *>(buffer);

  if (this->_buffer.size > 0)
    {
      if (cmdSize[this->_buffer.cmd[0]] - this->_buffer.size < size)
	{
	  memcpy(&this->_buffer.cmd[size - 1], buff, size);
	  this->_buffer.size += size;
	}
      else
	{
	  memcpy(&this->_buffer.cmd[size - 1], buff, cmdSize[this->_buffer.cmd[0]] - this->_buffer.size);
	  this->_buffer.size = cmdSize[this->_buffer.cmd[0]];
	  this->_readBuffer.push_back(this->_buffer);
	  for (int i = 0; i < GREATEST_COMMAND_SIZE; ++i)
	    this->_buffer.cmd[i] = -1;
	  this->_buffer.size = 0;
	}
    }
  for (int i = 0; i < size; ++i) {
    if (cmdSize[buff[i]] <= (size - 1) - i)
      {
	memcpy(this->_buffer.cmd, &buff[i], cmdSize[buff[i]]);
	this->_buffer.size = cmdSize[buff[i]];
	this->_readBuffer.push_back(this->_buffer);
	i += cmdSize[buff[i]];
	this->_buffer.size = 0;
      }
    else
      {
	memcpy(this->_buffer.cmd, &buff[i], (size - 1) - i);
	this->_buffer.size = (size - 1) - i;
	i = size - 1;
      }
  }
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

std::string const	&Client::getNickName() const
{
  return (this->_nickName);
}

void	Client::setNickName(const char *nickName)
{
  this->_nickName = nickName;
}

t_infos_game	*Client::getInfosClient() const
{
  return (const_cast<t_infos_game *>(&this->_infosClient));
}

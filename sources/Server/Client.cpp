#include "Client.h"

Client::Client(int id, MetaSocket<> *socket)
{
  this->_socket = socket;
  this->_id = id;
  this->_host = false;
  this->_infosClient = NULL;
  for (int i = 0; i < GREATEST_COMMAND_SIZE; ++i)
    this->_buffer.cmd[i] = -1;
  this->_buffer.size = 0;
  this->_nickName = "unknown";
}

Client::~Client() {}

/*ne pas oublie de delete infos_client quand la gameet fini*/
void			Client::setInfosClient()
{
	this->_infosClient = new t_infos_client;
	this->_infosClient->life = 3;
	this->_infosClient->weapon = MISSIL;
	this->_infosClient->bonus = false;
	this->_infosClient->score = 0;
	this->_infosClient->hightScore = 0;
	this->_infosClient->status = READY;
}

Status			Client::getStatus() const
{
	return (this->_status);
}

void			Client::setStatus(Status status)
{
	this->_status = status;
}

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

std::list<t_cmd_udp>*	Client::getReadBufferUDP()
{
	return (&this->_readBufferUDP);
}

char*					Client::getWriteBufferUDP()
{
	return (this->_writeBufferUDP);
}

struct sockaddr_in *	Client::getSockAddr()
{
	return (&this->_sin);
}

void		Client::parseCommand(void *buffer, unsigned int size, std::map<char, unsigned int> &cmdSize)
{
  char		*buff = reinterpret_cast<char *>(buffer);

  if (this->_buffer.size > 0)
    {
      if (cmdSize[this->_buffer.cmd[0]] - this->_buffer.size < size)
	{
	  memcpy(&this->_buffer.cmd[size], buff, size);
	  this->_buffer.size += size;
	}
      else
	{
	  memcpy(&this->_buffer.cmd[size], buff, cmdSize[this->_buffer.cmd[0]] - this->_buffer.size);
	  this->_buffer.size = cmdSize[this->_buffer.cmd[0]];
	  this->_readBuffer.push_back(this->_buffer);
	  for (int i = 0; i < GREATEST_COMMAND_SIZE; ++i)
	    this->_buffer.cmd[i] = -1;
	  this->_buffer.size = 0;
	}
    }
  for (unsigned int i = 0; i < size; ++i) {
    if (cmdSize[buff[i]] <= size - i)
      {
	memcpy(this->_buffer.cmd, &buff[i], cmdSize[buff[i]]);
	this->_buffer.size = cmdSize[buff[i]];
	std::cout << "je fou une commande dans le buffer read" << std::endl;
	this->_readBuffer.push_back(this->_buffer);
	i += cmdSize[buff[i]];
	this->_buffer.size = 0;
      }
    else
      {
	memcpy(this->_buffer.cmd, &buff[i], (size - 1) - i);
	this->_buffer.size =  size - i;
	i = size - 1;
      }
  }
}

void		Client::parseCommandUDP(void *buffer, unsigned int size, std::map<char, unsigned int> &cmdSize)
{
  char		*buff = reinterpret_cast<char *>(buffer);

  if (this->_bufferUDP.size > 0)
    {
      if (cmdSize[this->_bufferUDP.cmd[0]] - this->_bufferUDP.size < size)
	{
	  memcpy(&this->_bufferUDP.cmd[size], buff, size);
	  this->_bufferUDP.size += size;
	}
      else
	{
	  memcpy(&this->_bufferUDP.cmd[size], buff, cmdSize[this->_bufferUDP.cmd[0]] - this->_bufferUDP.size);
	  this->_bufferUDP.size = cmdSize[this->_bufferUDP.cmd[0]];
	  this->_readBufferUDP.push_back(this->_bufferUDP);
	  for (int i = 0; i < GREATEST_COMMAND_SIZE_UDP_PROTOCOL; ++i)
	    this->_bufferUDP.cmd[i] = -1;
	  this->_bufferUDP.size = 0;
	}
    }
  for (unsigned int i = 0; i < size; ++i) {
    if (cmdSize[buff[i]] <= size - i)
      {
	memcpy(this->_bufferUDP.cmd, &buff[i], cmdSize[buff[i]]);
	this->_bufferUDP.size = cmdSize[buff[i]];
	std::cout << "je fou une commande dans le buffer read UDP" << std::endl;
	this->_readBufferUDP.push_back(this->_bufferUDP);
	i += cmdSize[buff[i]];
	this->_bufferUDP.size = 0;
      }
    else
      {
	memcpy(this->_bufferUDP.cmd, &buff[i], (size - 1) - i);
	this->_bufferUDP.size =  size - i;
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

t_infos_client	*Client::getInfosClient() const
{
  return (const_cast<t_infos_client *>(this->_infosClient));
}

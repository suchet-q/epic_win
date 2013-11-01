//
// SocketLinux.cpp for zizi in /home/suchet_q//tek3/rtype/rtype
// 
// Made by quentin suchet
// Login   <suchet_q@epitech.net>
// 
// Started on  Sat Oct 12 14:35:59 2013 quentin suchet
// Last update Mon Oct 28 19:23:31 2013 geoffrey michelini
//

#include		<unistd.h>
#include		"Linux/SocketLinux.h"

SocketLinux::SocketLinux() : _socket(-1), _ifClosed(true), _type(NONE) {}

SocketLinux::~SocketLinux()
{
  if (!this->_ifClosed)
    close(this->_socket);
}

int					SocketLinux::getSocket() const
{
	return (this->_socket);
}

struct sockaddr_in	*SocketLinux::getSockaddr() const
{
  return (const_cast<struct sockaddr_in *>(&this->_sin));
}

bool			SocketLinux::isClosed() const
{
  return this->_ifClosed;
}

void			SocketLinux::setSocket(int socket)
{
  this->_socket = socket;
}

void			SocketLinux::setSin(struct sockaddr_in &sin)
{
  this->_sin = sin;
}

void			SocketLinux::setIfClosed(bool closed)
{
  this->_ifClosed = closed;
}

void			SocketLinux::setType(proto type)
{
  this->_type = type;
}

bool			SocketLinux::init(proto type)
{
  struct protoent*	proto;
  int			optval = 1;

  if (type == UDP)
    {
      if ((proto = getprotobyname("UDP")) == NULL)
	return (false);
      std::cout << "Protocol etablished\nCreating the socket..." << std::endl;

      if ((this->_socket = socket(AF_INET, SOCK_DGRAM, proto->p_proto)) == -1)
	return (false);
    }
  else if (type == TCP)
    {
      if ((proto = getprotobyname("TCP")) == NULL)
	return (false);
      std::cout << "Protocol etablished\nCreating the socket..." << std::endl;

      if ((this->_socket = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
	return false;
    }
  else
    return false;

  this->_type = type;
  this->_ifClosed = false;
  setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
  std::cout << "Socket created" << std::endl;
  return true;
}

bool			SocketLinux::Bind(char *ip, unsigned int port)
{

  if (this->_ifClosed)
    return false;

  if (!ip)
    this->_sin.sin_addr.s_addr = INADDR_ANY;
  else
    this->_sin.sin_addr.s_addr = inet_addr(ip);
  this->_sin.sin_family = AF_INET;
  this->_sin.sin_port = htons(port);

  std::cout << "Binding socket..." << std::endl;
  if (bind(this->_socket, reinterpret_cast<const struct sockaddr *>(&this->_sin), sizeof(this->_sin)) == -1)
    {
      std::cout << "Bind failed" << std::endl;
      return false;
    }
  std::cout << "Socket binded" << std::endl;
  return true;

}

bool			SocketLinux::Listen(int queue)
{
  if (this->_ifClosed == true || this->_type != TCP)
    return false;

  if (listen(this->_socket, queue) == -1)
    return false;
  return true;
}

bool			SocketLinux::Connect(char *ip, unsigned int port)
{
  struct sockaddr_in sin;

  if (this->_ifClosed == true || this->_type != TCP)
    return false;

  sin.sin_addr.s_addr = inet_addr(ip);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);

  if (connect(this->_socket, reinterpret_cast<struct sockaddr *>(&sin), sizeof(sin)))
    return false;
  return true;
}

SocketLinux		*SocketLinux::Accept()
{
  SocketLinux	*client;
  int			client_sock;
  struct sockaddr_in	clientsin;
  int			clientsin_size = sizeof(clientsin);

  if (this->_ifClosed || this->_type != TCP)
    return NULL;

  if ((client_sock = accept(this->_socket, reinterpret_cast<struct sockaddr*>(&clientsin), reinterpret_cast<socklen_t *>(&clientsin_size))) == -1)
    return NULL;

  client = new SocketLinux();
  client->setSocket(client_sock);
  client->setSin(clientsin);
  client->setIfClosed(false);
  client->setType(TCP);
  return client;
}

bool			SocketLinux::Close()
{
  if (this->_ifClosed)
    return false;
  close(this->_socket);
  this->_type = NONE;
  this->_ifClosed = true;
  return true;
}

int			SocketLinux::Recv(void *buffer, int size)
{
  if (this->_ifClosed)
    return UNINITIALIZED_SOCKET;
  if (this->_type != TCP)
    return BAD_PROTOCOL;

  return recv(this->_socket, buffer, size, 0);
}

int			SocketLinux::Send(const void *buffer, int size)
{
  if (this->_ifClosed)
    return UNINITIALIZED_SOCKET;
  if (this->_type != TCP)
    return BAD_PROTOCOL;

  return send(this->_socket, buffer, size, 0);
}

int		SocketLinux::sendTo(void *to_send, int size, struct sockaddr_in *dest)
{
  unsigned int		sended;

  if (this->_ifClosed)
    return (UNINITIALIZED_SOCKET);

  sended = sendto(this->_socket, to_send, size, 0, reinterpret_cast<struct sockaddr *>(dest), sizeof(*dest));
  return (sended);
}

int		SocketLinux::recvFrom(void *buff, int size, struct sockaddr_in *sender)
{
  socklen_t			size_sin;
  unsigned int		readed;

  if (this->_ifClosed)
    return (UNINITIALIZED_SOCKET);
  
  readed = recvfrom(this->_socket, buff, size, 0, reinterpret_cast<struct sockaddr *>(sender), &size_sin);
  return (readed);
}



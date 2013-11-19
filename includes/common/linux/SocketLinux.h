/*
** SocketLinuxUDP.h for zizi in /home/suchet_q//tek3/rtype/rtype
** 
** Made by quentin suchet
** Login   <suchet_q@epitech.net>
** 
** Started on  Sat Oct 12 14:35:56 2013 quentin suchet
// Last update Tue Nov 19 23:39:11 2013 geoffrey michelini
*/

#pragma once

#include <iostream>
#include <sstream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>

#define UNINITIALIZED_SOCKET (-2)
#define BAD_PROTOCOL (-3)

enum	proto
{
	NONE,
	TCP,
	UDP
};

class			SocketLinux
{
  int			_socket;
  struct sockaddr_in	_sin;
  bool			_ifClosed;
  proto			_type;

public:
  SocketLinux();
  ~SocketLinux();

  int					getSocket() const;
  struct sockaddr_in	*getSockaddr() const;
  bool			isClosed() const;
  void			setSocket(int);
  void			setSin(struct sockaddr_in &);
  void			setIfClosed(bool closed);
  void			setType(proto type);
  
  bool			init(proto type);
  bool			Bind(char const *ip, unsigned int port);
  bool			Listen(int queue);
  bool			Connect(char *ip, unsigned int port);
  SocketLinux	*Accept();

  bool			Close();

  int			Recv(void *buffer, int size);
  int			Send(const void *buffer, int size);
  int			sendTo(const void *to_send, int size, struct sockaddr_in *dest);
  int			recvFrom(void *buff, int size, struct sockaddr_in *sender);
};

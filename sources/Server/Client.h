#pragma once

# include	<iostream>
# include	<string>
# include	<list>

# include	"MetaSocket.h"

enum		Weapons
{
  MISSIL,
  LASER
};

typedef struct	s_infos_game
{
  int		life;
  Weapons	weapon;
  bool		bonus;
  int		score;
  int		hightScore;
}		t_infos_game;

class		Client
{
private:
  int		_id;
  bool		_host;
  char		_nickName[16];
  t_infos_game	_infosClient;
  MetaSocket<>	*_socket;
  std::list<std::pair<void *, unsigned int> >	_writeBuffer;
  std::list<std::pair<void *, unsigned int> >	_readBuffer;

public:
  Client(int, MetaSocket<> *);
  ~Client();

  std::list<std::pair<void *, unsigned int> >	&getWriteBuffer();
  std::list<std::pair<void *, unsigned int> >	&getReadBuffer();
  int		sendCommand();
  int		recvCommand();
  MetaSocket<>	*getSocket();
  int		getID();
  bool		getHost();
  void		setHost(bool);
  bool		setNickName(const char *);
  char	const	&getNickName();
  t_infos_game	&getInfosClient();
};


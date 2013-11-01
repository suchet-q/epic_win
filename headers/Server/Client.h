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
  std::string	_nickName;
  t_infos_game	_infosClient;
  MetaSocket<>	*_socket;
  std::list<std::pair<void *, unsigned int> >	_writeBuffer;
  std::list<std::pair<void *, unsigned int> >	_readBuffer;

public:
  Client(int, MetaSocket<> *);
  ~Client();

  std::list<std::pair<void *, unsigned int> >	*getWriteBuffer() const;
  std::list<std::pair<void *, unsigned int> >	*getReadBuffer() const;
  void		addMsgSend(void *, int);
  int		sendCommand();
  int		recvCommand();
  MetaSocket<>	*getSocket() const;
  int		getID() const;
  bool		getHost() const;
  void		setHost(bool);
  void		setNickName(const char *);
  std::string const	&getNickName() const;
  t_infos_game	*getInfosClient() const;
};


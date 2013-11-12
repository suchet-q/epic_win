#pragma once

# include	<iostream>
# include	<string>
# include	<cstring>
# include	<list>
# include	<map>

# include	"MetaSocket.h"
#include	"Game.h"

class Game;

# define	GREATEST_COMMAND_SIZE	(259)

enum		Status
{
	DEFAULT,
	CONNECTED,
	TO_LEAVE,
	TO_DECO
};

enum		Weapons
{
  MISSIL,
  LASER
};

enum		StatusInGame
{
	READY,
	DECO
};

typedef struct	s_infos_client
{
  int		life;
  Weapons	weapon;
  bool		bonus;
  int		score;
  int		hightScore;
  StatusInGame	status;
}				t_infos_client;

struct		t_cmd
{
  char		cmd[GREATEST_COMMAND_SIZE];
  unsigned int	size;
};

struct		t_UDPcmd
{
	t_cmd cmd;
	struct sockaddr_in sin;
};

class		Client
{
private:
  int		_id;
  bool		_host;
  Status	_status;
  std::string	_nickName;
  std::list<Game *>::iterator *_game;
  t_infos_client	*_infosClient;
  MetaSocket<>	*_socket;
  t_UDPcmd		_frameCMD;
  t_cmd		_buffer;
  std::list<t_cmd>	_writeBuffer;
  std::list<t_cmd>	_readBuffer;

public:
  Client(int, MetaSocket<> *);
  ~Client();
  std::list<Game *>::iterator *getGame();
  void				setGame(std::list<Game *>::iterator *);
  Status			getStatus() const;
  void				setStatus(Status);
  std::list<t_cmd>	*getWriteBuffer() const;
  std::list<t_cmd>	*getReadBuffer() const;
  void		parseCommand(void *, unsigned int, std::map<char, unsigned int> &);
  MetaSocket<>*	getSocket() const;
  int		getID() const;
  bool		getHost() const;
  void		setHost(bool);
  void		setNickName(const char *);
  std::string const	&getNickName() const;
  t_infos_client	*getInfosClient() const;
  void			setInfosClient();
};

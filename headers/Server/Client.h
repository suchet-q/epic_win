#pragma once

# include	<iostream>
# include	<string>
# include	<cstring>
# include	<list>
# include	<map>

# include	"MetaSocket.h"

# define	GREATEST_COMMAND_SIZE	(259)

enum		Weapons
{
  MISSIL,
  LASER
};

struct		t_infos_game
{
  int		life;
  Weapons	weapon;
  bool		bonus;
  int		score;
  int		hightScore;
};

struct		t_cmd
{
  char		cmd[GREATEST_COMMAND_SIZE];
  unsigned int	size;
};

class		Client
{
private:
  int		_id;
  bool		_host;
  std::string	_nickName;
  t_infos_game	_infosClient;
  MetaSocket<>	*_socket;
  t_cmd		_buffer;
  std::list<t_cmd>	_writeBuffer;
  std::list<t_cmd>	_readBuffer;

public:
  Client(int, MetaSocket<> *);
  ~Client();

  std::list<t_cmd>	*getWriteBuffer() const;
  std::list<t_cmd>	*getReadBuffer() const;
  void		parseCommand(void *, unsigned int, std::map<char, unsigned int> &);
  void		addMsgSend(void *, int);
  MetaSocket<>*	getSocket() const;
  int		getID() const;
  bool		getHost() const;
  void		setHost(bool);
  void		setNickName(const char *);
  std::string const	&getNickName() const;
  t_infos_game	*getInfosClient() const;
};

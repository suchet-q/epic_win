#pragma once

# include	<iostream>
# include	<string>
# include	<cstring>
# include	<list>
# include	<map>

# include	"MetaSocket.h"

# define	GREATEST_COMMAND_SIZE	(259)

enum		Status
{
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

class		Client
{
private:
  int		_id;
  bool		_host;
  Status	_status;
  std::string	_nickName;
  t_infos_client	*_infosClient;
  MetaSocket<>	*_socket;
  t_cmd		_buffer;
  std::list<t_cmd>	_writeBuffer;
  std::list<t_cmd>	_readBuffer;

public:
  Client(int, MetaSocket<> *);
  ~Client();
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

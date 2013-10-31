#pragma once
#include	<iostream>
#include	<string>

enum		Weapons
{
	MISSIL,
	LASER
};

typedef struct	s_infos_game
{
	int		life;
	Weapons	weapon;
	bool	bonus;
	int		score;
	int		hightScore;
}				t_infos_game;

class Client
{
private:
	int		_id;
	bool	_host;
	char	_nickName[16];
	t_infos_game	_infosClient;
public:
	Client(int);
	~Client();
	int		getID();
	bool	getHost();
	void	setHost(bool);
	bool	setNickName(const char *);
	char	const	&getNickName();
	t_infos_game	&getInfosClient();		
};


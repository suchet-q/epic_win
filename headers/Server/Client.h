#pragma once
#include	<iostream>
#include	<string>

enum		Weapons
{
	MISSIL,
	LASER
};

typedef struct	s_infos_client
{
	int		life;
	bool	host;
	char	nick_name[16];
	Weapons	weapon;
	bool	bonus;
	int		score;
	int		hightScore;
}				t_infos_client;

class Client
{
private:
	int		_id;
	t_infos_client	_infosClient;
public:
	Client();
	~Client();
};


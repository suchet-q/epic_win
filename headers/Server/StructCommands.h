#pragma once

/*send*/
typedef	struct			s_pnd_server
{
	unsigned char		id_command;
	unsigned char		id_client;
}						t_pnd_server;


/*send*/
typedef	struct			s_nbp_server
{
	unsigned char		id_command;
	unsigned char		nb_players;
}						t_nbp_server;
/*reciv*/
typedef	struct			s_nbp_client
{
	unsigned char		id_command;
}						t_nbp_client;


/*send*/
typedef struct			s_nbl_server
{
	unsigned char		id_command;
	unsigned char		id_lobby;
	unsigned char		lobby_nb_players;
}						t_nbl_server;
/*reciv*/
typedef	struct			s_nbl_client
{
	unsigned char		id_command;
}						t_nbl_client;


/*send*/
typedef	struct			s_jnl_server
{
	unsigned char		id_command;
	unsigned char		reponse;
}						t_jnl_server;
/*reciv*/
typedef	struct			s_jnl_client
{
	unsigned char		id_command;
	unsigned char		id_client;
	unsigned char		id_lobby;
}						t_jnl_client;


/*send*/
typedef struct			s_crl_server
{
	unsigned char		id_command;
	unsigned char		id_lobby;
}						t_crl_server;
/*reciv*/
typedef struct			s_crl_client
{
	unsigned char		id_command;
	unsigned char		id_client;
}						t_crl_client;


/*send*/
typedef struct			s_plj_server
{
	unsigned char		id_command;
	unsigned char		id_client;
	char				nick_name[16];
}						t_plj_server;


/*send*/
typedef	struct			s_stl_server
{
	unsigned char		id_command;
	unsigned char		response;
}						t_stl_server;
/*reciv*/
typedef	struct			s_stl_client
{
	unsigned char		id_command;
	unsigned char		id_lobby;
}						t_stl_client;


/*send*/
typedef	struct			s_msg_server
{
	unsigned char		id_command;
	unsigned char		id_client;
	char				msg[256];
}						t_msg_server;
/*reciv*/
typedef	struct			s_msg_client
{
	unsigned char		id_command;
	unsigned char		id_lobby;
	unsigned char		id_client;
	char				msg[256];
}						t_msg_client;


/*send*/
typedef	struct			s_nmp_server
{
	unsigned char		id_command;
	unsigned char		response;
}						t_nmp_server;
/*reciv*/
typedef	struct			s_nmp_client
{
	unsigned char		id_command;
	unsigned char		id_client;
	char				nick_name[16];
}						t_nmp_client;


/*send*/
typedef	struct			s_lvl_server
{
	unsigned char		id_command;
	unsigned char		id_client;
}						t_lvl_server;
/*reciv*/
typedef	struct			s_lvl_client
{
	unsigned char		id_command;
	unsigned char		id_lobby;
	unsigned char		id_client;
}						t_lvl_client;
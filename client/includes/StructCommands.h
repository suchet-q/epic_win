#pragma once

typedef	struct			s_pnb_server
{
	unsigned char		id_command;
	unsigned char		id_client;
}						t_pnb_server;

typedef	struct			s_nbp_server
{
	unsigned char		id_command;
	unsigned char		nb_players;
}						t_nbp_server;

typedef	struct			s_nbp_client
{
	unsigned char		id_command;
}						t_nbp_client;

typedef struct			s_nbl_server
{
	unsigned char		id_command;
	unsigned char		id_lobby;
	unsigned char		lobby_nb_players;
}						t_nbl_server;

typedef	struct			s_nbl_client
{
	unsigned char		id_commmand;
}						t_nbl_client;

typedef	struct			s_jnl_server
{
	unsigned char		id_command;
	unsigned char		reponse;
}						t_jnl_server;

typedef	struct			s_jnl_client
{
	unsigned char		id_command;
	unsigned char		id_client;
	unsigned char		id_lobby;
}						t_jnl_client;


typedef struct			s_crl_server
{
	unsigned char		id_command;
	unsigned char		id_lobby;
}						t_crl_server;

typedef struct			s_crl_client
{
	unsigned char		id_command;
	unsigned char		id_client;
}						t_crl_client;

typedef struct			s_plj_server
{
	unsigned char		id_command;
	unsigned char		id_client;
	char				nick_name[16];
}						t_plj_server;

typedef	struct			s_stl_server
{
	unsigned char		id_command;
	unsigned char		response;
}						t_stl_server;

typedef	struct			s_stl_client
{
	unsigned char		id_command;
	unsigned char		id_lobby;
}						t_stl_client;

typedef	struct			s_msg_server
{
	unsigned char		id_command;
	unsigned char		id_client;
	char				msg[256];
}						t_msg_server;

typedef	struct			s_msg_client
{
	unsigned char		id_command;
	unsigned char		id_lobby;
	unsigned char		id_client;
	char				msg[256];
}						t_msg_client;

typedef	struct			s_nmp_server
{
	unsigned char		id_command;
	unsigned char		response;
}						t_nmp_server;

typedef	struct			s_nmp_client
{
	unsigned char		id_command;
	unsigned char		id_client;
	char				nick_name[16];
}						t_nmp_client;

typedef	struct			s_lvl_server
{
	unsigned char		id_command;
	unsigned char		id_client;
}						t_lvl_server;

typedef	struct			s_lvl_client
{
	unsigned char		id_command;
	unsigned char		id_lobby;
	unsigned char		id_client;
}						t_lvl_client;

typedef struct			s_aff_server
{
	unsigned char		id_cmd;
	unsigned char		type;
	unsigned short		id_obj;
	unsigned short		x;
	unsigned short		y;
}						t_aff_server;

typedef struct			s_scr_server
{
	unsigned char		id_cmd;
	unsigned short		score;
}						t_scr_server;

typedef struct			s_lif_server
{
	unsigned char		id_cmd;
	unsigned char		life;
}						t_lif_server;

typedef struct			s_evt_server
{
	unsigned char		id_cmd;
	unsigned char		event;
}						t_evt_server;

typedef struct			s_inp_client
{
	unsigned char		id_cmd;
	unsigned char		id_client;
	unsigned short		input;
}						t_inp_client;

typedef struct			s_idt_client
{
	unsigned char		id_cmd;
	unsigned char		id_client;
}						t_idt_client;
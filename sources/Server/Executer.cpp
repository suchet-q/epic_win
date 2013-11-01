#include "Executer.h"


Executer::Executer()
{
}


Executer::~Executer()
{
}

void			Executer::execPND(void *command, int size)
{
	/*envoie ID unique du nouveau client*/
}

void			Executer::execNBP(void *command, int size)
{
	t_nbp_client	*nbp;

	nbp = reinterpret_cast<t_nbp_client *>(command);
}

void			Executer::execNBL(void *command, int size)
{
	t_nbl_client	*nbl;

	nbl = reinterpret_cast<t_nbl_client *>(command);
}

void			Executer::execJNL(void *command, int size)
{
	t_jnl_client	*jnl;

	jnl = reinterpret_cast<t_jnl_client *>(command);
}

void			Executer::execCRL(void *command, int size)
{
	t_crl_client	*crl;

	crl = reinterpret_cast<t_crl_client *>(command);
}

void			Executer::execPLJ(void *command, int size)
{
	/*indique au client qu'un nouveau player a rejoint le lobby*/
}

void			Executer::execSTL(void *command, int size)
{
	t_stl_client	*stl;

	stl = reinterpret_cast<t_stl_client *>(command);
}

void			Executer::execMSG(void *command, int size)
{
	t_msg_client	*msg;

	msg = reinterpret_cast<t_msg_client *>(command);
}

void			Executer::execNMP(void *command, int size)
{
	t_nmp_client	*nmp;

	nmp = reinterpret_cast<t_nmp_client *>(command);
}

void			Executer::execLVL(void *command, int size)
{
	t_lvl_client	*lvl;

	lvl = reinterpret_cast<t_lvl_client *>(command);
}
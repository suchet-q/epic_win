#pragma once
#include	"StructCommands.h"
#include	"Resource.h"

class	Executer;

typedef	bool	(Executer::*exec)(Client *, t_cmd const &);

class Executer
{
private:
	Resource	*_resource;
	exec		*_func;
public:
	Executer();
	~Executer();
	bool			executCommand(Client *client, t_cmd const &command);
	void			setResource(Resource *);
	bool			execNBP(Client *client, t_cmd const &);
	bool			execNBL(Client *client, t_cmd const &);
	bool			execJNL(Client *client, t_cmd const &);
	bool			execCRL(Client *client, t_cmd const &);
	bool			execSTL(Client *client, t_cmd const &);
	bool			execMSG(Client *client, t_cmd const &);
	bool			execNMP(Client *client, t_cmd const &);
	bool			execLVL(Client *client, t_cmd const &);
};
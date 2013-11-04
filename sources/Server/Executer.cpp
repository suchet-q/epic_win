#include "Executer.h"

Executer::Executer()
{
	this->_func = new exec[10];
	this->_func[1] = &Executer::execNBP;
	this->_func[2] = &Executer::execNBL;
	this->_func[3] = &Executer::execJNL;
	this->_func[4] = &Executer::execCRL;
	this->_func[6] = &Executer::execSTL;
	this->_func[7] = &Executer::execMSG;
	this->_func[8] = &Executer::execNMP;
	this->_func[9] = &Executer::execLVL;
}

Executer::~Executer()
{
}

bool			Executer::executCommand(Client *client, t_cmd const &command)
{

	std::cout << "la commande est : " << (int)command.cmd[0] << std::endl;
	return ((this->*_func[command.cmd[0]])(client, command));
}

void			Executer::setResource(Resource *resource)
{
	this->_resource = resource;
}

bool			Executer::execNBP(Client *client, t_cmd const &command)
{
	t_nbp_client	nbp;
	t_nbp_server	answer;
	t_cmd			cmd;

	memcpy(&nbp, command.cmd, sizeof(t_nbp_client));
	answer.id_command = nbp.id_command;
	answer.nb_players = this->_resource->getClients().size();
	memcpy(cmd.cmd, &answer, sizeof(t_nbp_server));
	cmd.size = sizeof(t_nbp_server);
	client->getWriteBuffer()->push_back(cmd);
	return (true);
}

bool			Executer::execNBL(Client *client, t_cmd const &command)
{
	t_nbl_client	nbl;
	t_nbl_server	tmp;
	t_cmd		awnser;
  
	memcpy(&nbl, command.cmd, sizeof(t_nbl_client));
	tmp.id_command = nbl.id_command;
	awnser.size = sizeof(t_nbl_server);
	for (std::list<Room *>::const_iterator it = _resource->getRooms().begin();
		it != _resource->getRooms().end(); ++it)
	{
		tmp.id_lobby = (*it)->getID();
		tmp.lobby_nb_players = (*it)->getClient()->size();
		memcpy(awnser.cmd, &tmp, sizeof(t_nbl_server));
		client->getWriteBuffer()->push_back(awnser);
	}
	return (true);
}

bool			Executer::execJNL(Client *client, t_cmd const &command)
{
	t_jnl_client	jnl;
	t_jnl_server	answer;
	t_cmd			cmd;

	memcpy(&jnl, command.cmd, sizeof(t_jnl_client));
	for (std::list<Room *>::iterator it = this->_resource->getRooms().begin();
			it != this->_resource->getRooms().end(); ++it)
	{
		if ((*it)->getID() == jnl.id_lobby)
		{
			if ((*it)->addClient(client) == false)
			{
				answer.id_command = jnl.id_command;
				answer.reponse = 0;
				memcpy(cmd.cmd, &answer, sizeof(t_jnl_server));
				cmd.size = sizeof(t_jnl_server);
				client->getWriteBuffer()->push_back(cmd);
				return (false);
			}
			answer.id_command = jnl.id_command;
			answer.reponse = 1;
			memcpy(cmd.cmd, &answer, sizeof(t_jnl_server));
			cmd.size = sizeof(t_jnl_server);
			client->getWriteBuffer()->push_back(cmd);
			return (true);
		}
	}
	return (true);
}

bool			Executer::execCRL(Client *client, t_cmd const &command)
{
	t_plj_server	plj;
	t_crl_client	crl;
	t_crl_server	tmp;
	t_cmd		awnser;
	bool		success = false;
  
	memcpy(&crl, command.cmd, sizeof(t_crl_client));
	tmp.id_command = crl.id_command;
	if (!_resource->createRoom(client))
		tmp.id_lobby = 0;
	else {
		tmp.id_lobby = _resource->getRooms().back()->getID();
		plj.id_client = crl.id_client;
		plj.id_command = 5;
		memcpy(plj.nick_name, client->getNickName().c_str(), client->getNickName().size());
		if (client->getNickName().size() < 16)
			plj.nick_name[client->getNickName().size()] = '\0';
		success = true;
		std::cout << "je vais ajouter" << std::endl;
		_resource->getRooms().back()->addClient(client);
		_resource->getRooms().back()->setHost(client);
		std::cout << "jai ajoute" << std::endl;
	}
	std::cout << "tmp.id_lobby = " << (int)tmp.id_lobby << std::endl;
	memcpy(awnser.cmd, &tmp, sizeof(t_crl_server));
	awnser.size = sizeof(t_crl_server);
	client->getWriteBuffer()->push_back(awnser);
	if (success)
	{
		memcpy(awnser.cmd, &plj, sizeof(t_plj_server));
		awnser.size = sizeof(t_plj_server);
		client->getWriteBuffer()->push_back(awnser);
	}
	return true;
}

bool			Executer::execSTL(Client *client, t_cmd const &command)
{
	t_stl_client	stl;
	std::list<Room *>::iterator it = this->_resource->getRooms().begin();
	t_stl_server	answer;
	t_cmd			cmd;
	bool			succeed = false;

	/*lauch game if succeed, succeed = true*/
	memcpy(&stl, command.cmd, sizeof(t_jnl_client));
	for (; it != this->_resource->getRooms().end(); ++it)
	{
		if ((*it)->getID() == stl.id_lobby)
		{
			std::list<Client *>::iterator itc = (*it)->getClient()->begin();
			answer.id_command = stl.id_command;
			if (succeed == true)
				answer.response = 1;
			else
				answer.response = 0;
			memcpy(cmd.cmd, &answer, sizeof(t_stl_server));
			cmd.size = sizeof(t_stl_server);
			for (; itc != (*it)->getClient()->end(); ++itc)
			{
				(*itc)->getWriteBuffer()->push_back(cmd);
			}
			if (succeed == true)
			{
				it = this->_resource->getRooms().erase(it);
				return (true);
			}
			else
				return (false);
		}
	}
	return (false);
}

bool			Executer::execMSG(Client *client, t_cmd const &command)
{
	std::list<Room *>::const_iterator it;
	t_msg_client	msg;
	t_msg_server	tmp;
	t_cmd		awnser;
  
	memcpy(&msg, command.cmd, sizeof(t_msg_client));
	tmp.id_command = msg.id_command;
	tmp.id_client = msg.id_client;
	memcpy(tmp.msg, msg.msg, 256 * sizeof(char));
	memcpy(awnser.cmd, &tmp, sizeof(t_msg_server));
	awnser.size = sizeof(t_msg_server);
	for (it = _resource->getRooms().begin();
		it != _resource->getRooms().end() && (*it)->getID() != msg.id_lobby; ++it);
	if ((*it)->getID() == msg.id_lobby)
		for (std::list<Client *>::const_iterator itc = _resource->getClients().begin();
			itc != _resource->getClients().end(); ++itc)
				(*itc)->getWriteBuffer()->push_back(awnser);
	return true;
}

bool			Executer::execNMP(Client *client, t_cmd const &command)
{
	t_nmp_client	nmp;

	memcpy(&nmp, command.cmd, sizeof(t_nmp_client));	
	client->setNickName(nmp.nick_name);
	return (true);
}

bool			Executer::execLVL(Client *client, t_cmd const &command)
{
	std::list<Room *>::iterator	it;
	std::list<Client *>::iterator	itc;
	t_lvl_client	lvl;
	t_lvl_server	tmp;
	t_cmd		awnser;
  
	memcpy(&lvl, command.cmd, sizeof(t_lvl_client));
	tmp.id_command = lvl.id_command;
	tmp.id_client = lvl.id_client;
	memcpy(awnser.cmd, &tmp, sizeof(t_lvl_server));
	awnser.size = sizeof(t_lvl_server);
	std::cout << "step 1" << std::endl;
	for (it = _resource->getRooms().begin();
		it != _resource->getRooms().end() && (*it)->getID() != lvl.id_lobby; ++it);
	std::cout << "step 2" << std::endl;
	if ((*it)->getID() == lvl.id_lobby)
	{
 		for (itc = (*it)->getClient()->begin();
			itc != (*it)->getClient()->end() && (*itc)->getID() != lvl.id_client; ++itc);

		for (std::list<Client *>::iterator itx = (*it)->getClient()->begin();
			itx != (*it)->getClient()->end(); ++itx) {
				std::cout << "prout" << std::endl;
		}

		if (itc != (*it)->getClient()->end())
		{
			if ((*itc) == (*it)->getHost())
			{
				for (std::list<Client *>::iterator itc_c = (*it)->getClient()->begin();
					itc_c != (*it)->getClient()->end(); ++itc_c)
				{
					tmp.id_client = (*itc_c)->getID();
					memcpy(awnser.cmd, &tmp, sizeof(t_lvl_server));
					awnser.size = sizeof(t_lvl_server);
					(*itc_c)->getWriteBuffer()->push_back(awnser);
					itc_c = (*it)->getClient()->erase(itc_c);
					if (itc_c == (*it)->getClient()->end())
						break;
				}
				it = _resource->deleteRoom(it);
			}
			else
			{
				std::cout << "step 6" << std::endl;
				for (std::list<Client *>::iterator itc_c = (*it)->getClient()->begin();
					itc_c != (*it)->getClient()->end(); ++itc_c)
				{
					(*itc_c)->getWriteBuffer()->push_back(awnser);
					if ((*itc_c)->getID() == lvl.id_client)
						itc_c = (*it)->getClient()->erase(itc_c);
				}
			}
		}
	}
	std::cout << "return "<< std::endl;
	return true;
}
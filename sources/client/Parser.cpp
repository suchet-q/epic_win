#include <iostream>
#include "Parser.h"

Parser::Parser(void)
{
	this->_functions[CMD_PNB] = &Parser::parsePNB;
	this->_functions[CMD_NBP] = &Parser::parseNBP;
	this->_functions[CMD_NBL] = &Parser::parseNBL;
	this->_functions[CMD_JNL] = &Parser::parseJNL;
	this->_functions[CMD_CRL] = &Parser::parseCRL;
	this->_functions[CMD_PLJ] = &Parser::parsePLJ;
	this->_functions[CMD_STL] = &Parser::parseSTL;
	this->_functions[CMD_MSG] = &Parser::parseMSG;
	this->_functions[CMD_LVL] = &Parser::parseLVL;
	this->_functions[CMD_NMP] = &Parser::parseNMP;
	this->_functions[CMD_AFF] = &Parser::parseAFF;
	this->_functions[CMD_SCR] = &Parser::parseSCR;
	this->_functions[CMD_LIF] = &Parser::parseLIF;
	this->_functions[CMD_EVT] = &Parser::parseEVT;

	this->_castArray[CMD_PNB] = sizeof(t_pnb_server);
	this->_castArray[CMD_NBP] = sizeof(t_nbp_server);
	this->_castArray[CMD_NBL] = sizeof(t_nbl_server);
	this->_castArray[CMD_JNL] = sizeof(t_jnl_server);
	this->_castArray[CMD_CRL] = sizeof(t_crl_server);
	this->_castArray[CMD_PLJ] = sizeof(t_plj_server);
	this->_castArray[CMD_STL] = sizeof(t_stl_server);
	this->_castArray[CMD_MSG] = sizeof(t_msg_server);
	this->_castArray[CMD_LVL] = sizeof(t_lvl_server);
	this->_castArray[CMD_NMP] = sizeof(t_nmp_server);
	this->_castArray[CMD_AFF] = sizeof(t_aff_server);
	this->_castArray[CMD_SCR] = sizeof(t_scr_server);
	this->_castArray[CMD_LIF] = sizeof(t_lif_server);
	this->_castArray[CMD_EVT] = sizeof(t_evt_server);

	this->_cmdSize = 0;
	this->_startUDP = false;
}

Parser::~Parser(void)
{
}

void		Parser::addCallback(unsigned char id, cFunctor functor)
{
	this->_callbacks[id].push_back(functor);
}

void		Parser::parse(void* command, int size)
{
	char	cmd[512];
	int		cmd_size;

	while (size > 0)
	{
		//std::cout << "Parsing command of " << size << " bytes" << std::endl;
		memset(cmd, '\0', 512);
		if (this->_cmdSize)
		{
			memcpy(cmd, this->_cmd, this->_cmdSize);
			memcpy(&cmd[this->_cmdSize], command, this->_castArray[(this->_cmd)[0]] - this->_cmdSize);
			cmd_size = this->_castArray[(this->_cmd)[0]];
			this->_cmdSize = 0;
		}
		else
		{
			if (size < this->_castArray[static_cast<unsigned char *>(command)[0]])
			{
				memset(this->_cmd, '\0', 512);
				memcpy(this->_cmd, command, size);
				this->_cmdSize = size;
				size = 0;
				cmd_size = 0;
			}
			else
			{
				memcpy(cmd, command, this->_castArray[static_cast<unsigned char *>(command)[0]]);
				cmd_size = this->_castArray[static_cast<unsigned char *>(command)[0]];
				size -= cmd_size;
				command = this->_castArray[static_cast<unsigned char *>(command)[0]] + static_cast<unsigned char *>(command);
			}
		}
		if (cmd_size && this->_functions.find(cmd[0]) != this->_functions.end())
			(this->*this->_functions[cmd[0]])(cmd, cmd_size);
	}
	
}

void		Parser::parseAFF(void *command, int size)
{
	t_aff_server					cmd;
	std::list<boost::any>			args;
	std::list<cFunctor>::iterator	it;

	//std::cout << "Executing AFF on " << size << " bytes" << std::endl;
	if (size == sizeof(t_aff_server) && this->_callbacks.find(CMD_AFF) != this->_callbacks.end())
	{
		memcpy(&cmd, command, size);
		args.push_back(cmd.type);
		args.push_back(cmd.id_obj);
		args.push_back(cmd.x);
		args.push_back(cmd.y);
		for (it = this->_callbacks[CMD_AFF].begin(); it != this->_callbacks[CMD_AFF].end(); ++it)
			(*it)(args);
	}
}

void		Parser::parseSCR(void *command, int size)
{
	t_scr_server					cmd;
	std::list<boost::any>			args;
	std::list<cFunctor>::iterator	it;

	//std::cout << "Executing SCR on " << size << " bytes" << std::endl;
	if (size == sizeof(t_scr_server) && this->_callbacks.find(CMD_SCR) != this->_callbacks.end())
	{
		memcpy(&cmd, command, size);
		args.push_back(cmd.score);
		for (it = this->_callbacks[CMD_SCR].begin(); it != this->_callbacks[CMD_SCR].end(); ++it)
			(*it)(args);
	}
}

void		Parser::parseLIF(void *command, int size)
{
	t_lif_server					cmd;
	std::list<boost::any>			args;
	std::list<cFunctor>::iterator	it;

	//std::cout << "Executing LIF on " << size << " bytes" << std::endl;
	if (size == sizeof(t_lif_server) && this->_callbacks.find(CMD_LIF) != this->_callbacks.end())
	{
		memcpy(&cmd, command, size);
		args.push_back(cmd.life);
		for (it = this->_callbacks[CMD_LIF].begin(); it != this->_callbacks[CMD_LIF].end(); ++it)
			(*it)(args);
	}
}

void		Parser::parseEVT(void *command, int size)
{
	t_evt_server					cmd;
	std::list<boost::any>			args;
	std::list<cFunctor>::iterator	it;

	//std::cout << "Executing EVT on " << size << " bytes" << std::endl;
	if (size == sizeof(t_evt_server) && this->_callbacks.find(CMD_EVT) != this->_callbacks.end())
	{
		memcpy(&cmd, command, size);
		args.push_back(cmd.event);
		for (it = this->_callbacks[CMD_EVT].begin(); it != this->_callbacks[CMD_EVT].end(); ++it)
			(*it)(args);
	}
}

void		Parser::parsePNB(void *command, int size)
{
	t_pnb_server	cmd;
	std::list<boost::any>			args;
	std::list<cFunctor>::iterator	it;

	std::cout << "Executing PNB on " << size << " bytes" << std::endl;
	if (size == sizeof(t_pnb_server) && this->_callbacks.find(CMD_PNB) != this->_callbacks.end())
	{
		memcpy(&cmd, command, size);
		args.push_back(cmd.id_client);
		std::cout << "Received id CLIENT : " << (int)cmd.id_client << std::endl;
		for (it = this->_callbacks[CMD_PNB].begin(); it != this->_callbacks[CMD_PNB].end(); ++it)
			(*it)(args);
	}
}

void		Parser::parseNBP(void *command, int size)
{
	t_nbp_server	cmd;
	std::list<boost::any>			args;
	std::list<cFunctor>::iterator	it;

	std::cout << "Executing NBP on " << size << " bytes" << std::endl;
	if (size == sizeof(t_nbp_server) && this->_callbacks.find(CMD_NBP) != this->_callbacks.end())
	{
		memcpy(&cmd, command, size);
		args.push_back(cmd.nb_players);
		for (it = this->_callbacks[CMD_NBP].begin(); it != this->_callbacks[CMD_NBP].end(); ++it)
			(*it)(args);
	}
}

void		Parser::parseNBL(void *command, int size)
{
	t_nbl_server	cmd;
	std::list<boost::any>			args;
	std::list<cFunctor>::iterator	it;

	std::cout << "Executing NBL on " << size << " bytes" << std::endl;
	if (size == sizeof(t_nbl_server) && this->_callbacks.find(CMD_NBL) != this->_callbacks.end())
	{
		memcpy(&cmd, command, size);
		args.push_back(cmd.id_lobby);
		args.push_back(cmd.lobby_nb_players);
		for (it = this->_callbacks[CMD_NBL].begin(); it != this->_callbacks[CMD_NBL].end(); ++it)
			(*it)(args);
	}
}

void		Parser::parseJNL(void *command, int size)
{
	t_jnl_server	cmd;
	std::list<boost::any>			args;
	std::list<cFunctor>::iterator	it;

	std::cout << "Executing JNL on " << size << " bytes" << std::endl;
	if (size == sizeof(t_jnl_server) && this->_callbacks.find(CMD_JNL) != this->_callbacks.end())
	{
		memcpy(&cmd, command, size);
		args.push_back(cmd.reponse);
		for (it = this->_callbacks[CMD_JNL].begin(); it != this->_callbacks[CMD_JNL].end(); ++it)
			(*it)(args);
	}
}

void		Parser::parseCRL(void *command, int size)
{
	t_crl_server	cmd;
	std::list<boost::any>			args;
	std::list<cFunctor>::iterator	it;

	std::cout << "Executing CRL on " << size << " bytes" << std::endl;
	if (size == sizeof(t_crl_server) && this->_callbacks.find(CMD_CRL) != this->_callbacks.end())
	{
		memcpy(&cmd, command, size);
		args.push_back(cmd.id_lobby);
		for (it = this->_callbacks[CMD_CRL].begin(); it != this->_callbacks[CMD_CRL].end(); ++it)
			(*it)(args);
	}
}

void		Parser::parsePLJ(void *command, int size)
{
	t_plj_server	cmd;
	std::list<boost::any>			args;
	std::list<cFunctor>::iterator	it;
	std::string						nickName;
	
	std::cout << "Executing PLJ on " << size << " bytes" << std::endl;
	if (size == sizeof(t_plj_server) && this->_callbacks.find(CMD_PLJ) != this->_callbacks.end())
	{
		memcpy(&cmd, command, size);
		args.push_back(cmd.id_client);
		std::cout << "Received name : ";
		for (int i = 0; i < 16; ++i)
			std::cout << (int)(cmd.nick_name[i]);
		std::cout << std::endl;
		nickName = cmd.nick_name;
		args.push_back(nickName);
		for (it = this->_callbacks[CMD_PLJ].begin(); it != this->_callbacks[CMD_PLJ].end(); ++it)
			(*it)(args);
	}
}

void		Parser::parseSTL(void *command, int size)
{
	t_stl_server	cmd;
	std::list<boost::any>			args;
	std::list<cFunctor>::iterator	it;

	std::cout << "Executing STL on " << size << " bytes" << std::endl;
	if (size == sizeof(t_stl_server) && this->_callbacks.find(CMD_STL) != this->_callbacks.end())
	{
		memcpy(&cmd, command, size);
		args.push_back(cmd.response);
		args.push_back(cmd.port);
		std::cout << "Port received : " << cmd.port << std::endl;
		for (it = this->_callbacks[CMD_STL].begin(); it != this->_callbacks[CMD_STL].end(); ++it)
			(*it)(args);
	}
}

void		Parser::parseMSG(void *command, int size)
{
	t_msg_server	cmd;
	std::list<boost::any>			args;
	std::list<cFunctor>::iterator	it;
	std::string						msg;

	std::cout << "Executing MSG on " << size << " bytes" << std::endl;
	if (size == sizeof(t_msg_server) && this->_callbacks.find(CMD_MSG) != this->_callbacks.end())
	{
		memcpy(&cmd, command, size);
		args.push_back(cmd.id_client);
		msg = cmd.msg;
		args.push_back(msg);
		for (it = this->_callbacks[CMD_MSG].begin(); it != this->_callbacks[CMD_MSG].end(); ++it)
			(*it)(args);
	}
}

void		Parser::parseNMP(void *command, int size)
{
	t_nmp_server	cmd;
	std::list<boost::any>			args;
	std::list<cFunctor>::iterator	it;

	std::cout << "Executing NMP on " << size << " bytes" << std::endl;
	if (size == sizeof(t_nmp_server) && this->_callbacks.find(CMD_NMP) != this->_callbacks.end())
	{
		memcpy(&cmd, command, size);
		args.push_back(cmd.response);
		for (it = this->_callbacks[CMD_NMP].begin(); it != this->_callbacks[CMD_NMP].end(); ++it)
			(*it)(args);
	}
}

void		Parser::parseLVL(void *command, int size)
{
	t_lvl_server	cmd;
	std::list<boost::any>			args;
	std::list<cFunctor>::iterator	it;

	std::cout << "Executing LVL on " << size << " bytes" << std::endl;
	if (size == sizeof(t_lvl_server) && this->_callbacks.find(CMD_LVL) != this->_callbacks.end())
	{
		memcpy(&cmd, command, size);
		args.push_back(cmd.id_client);
		for (it = this->_callbacks[CMD_LVL].begin(); it != this->_callbacks[CMD_LVL].end(); ++it)
			(*it)(args);
	}
}

std::pair<void *, int>	Parser::getQueued()
{
	std::pair<void *, int>	ret;

	ret.first = NULL;
	if (this->_queued.size())
	{
		ret = this->_queued.front();
		this->_queued.pop_front();
	}
	return (ret);
}

void					Parser::setStartUDP()
{
	this->_startUDP = true;
}

bool					Parser::getStartUDP()
{
	return (this->_startUDP);
}

std::pair<void *, int>	Parser::getQueuedUDP()
{
	std::pair<void *, int>	ret;

	ret.first = NULL;
	if (this->_queuedUDP.size())
	{
		ret = this->_queuedUDP.front();
		this->_queuedUDP.pop_front();
	}
	return (ret);
}

void		Parser::addNBL()
{
	t_nbl_client	*cmd;

	std::cout << "Queued NBL" << std::endl;
	cmd = new t_nbl_client;
	cmd->id_command = CMD_NBL;
	this->_queued.push_back(std::pair<void *, int>(cmd, sizeof(t_nbl_client)));
}

void		Parser::addNBP()
{
	t_nbp_client	*cmd;

	std::cout << "Queued NBP" << std::endl;
	cmd = new t_nbp_client;
	cmd->id_command = CMD_NBP;
	this->_queued.push_back(std::pair<void *, int>(cmd, sizeof(t_nbp_client)));
}

void		Parser::addSTL(int idLobby)
{
	t_stl_client	*cmd;

	std::cout << "Queued STL" << std::endl;
	cmd = new t_stl_client;
	cmd->id_command = CMD_STL;
	cmd->id_lobby = idLobby;
	this->_queued.push_back(std::pair<void *, int>(cmd, sizeof(t_stl_client)));

}

void		Parser::addJNL(unsigned char idClient, unsigned char idLobby)
{
	t_jnl_client	*cmd;

	std::cout << "Queued JNL" << std::endl;
	cmd = new t_jnl_client;
	cmd->id_command = CMD_JNL;
	cmd->id_client = idClient;
	cmd->id_lobby = idLobby;
	this->_queued.push_back(std::pair<void *, int>(cmd, sizeof(t_jnl_client)));
}

void		Parser::addCRL(unsigned char idClient)
{
	t_crl_client	*cmd;

	std::cout << "Queued CRL" << std::endl;
	cmd = new t_crl_client;
	cmd->id_command = CMD_CRL;
	cmd->id_client = idClient;
	this->_queued.push_back(std::pair<void *, int>(cmd, sizeof(t_crl_client)));
}

void		Parser::addNMP(unsigned char idClient, std::string const &nick)
{
	t_nmp_client	*cmd;
	char			*str;

	std::cout << "Queued NMP" << std::endl;
	cmd = new t_nmp_client;
	cmd->id_command = CMD_NMP;
	cmd->id_client = idClient;
	str = const_cast<char *>(nick.c_str());
	for (int i = 0; i < 16; ++i)
		if (str[i] != '\0')
			cmd->nick_name[i] = str[i];
		else
			cmd->nick_name[i] = '\0';
	this->_queued.push_back(std::pair<void *, int>(cmd, sizeof(t_nmp_client)));
}

void		Parser::addMSG(unsigned char idClient, unsigned char idLobby, std::string const &nick)
{
	t_msg_client	*cmd;
	char			*str;

	std::cout << "Queued MSG" << std::endl;
	cmd = new t_msg_client;
	cmd->id_command = CMD_MSG;
	cmd->id_client = idClient;
	cmd->id_lobby = idLobby;
	str = const_cast<char *>(nick.c_str());
	for (int i = 0; i < 256; ++i)
		if (str[i] != '\0')
			cmd->msg[i] = str[i];
		else
			cmd->msg[i] = '\0';
	this->_queued.push_back(std::pair<void *, int>(cmd, sizeof(t_msg_client)));
}

void		Parser::addLVL(unsigned char idClient, unsigned char idLobby)
{
	t_lvl_client	*cmd;

	std::cout << "Queued LVL" << std::endl;
	cmd = new t_lvl_client;
	cmd->id_command = CMD_LVL;
	cmd->id_client = idClient;
	cmd->id_lobby = idLobby;
	this->_queued.push_back(std::pair<void *, int>(cmd, sizeof(t_lvl_client)));
}

void		Parser::addINP(unsigned char idClient, unsigned short input)
{
	t_inp_client	*cmd;

	std::cout << "Queued INP" << std::endl;
	cmd = new t_inp_client;
	cmd->id_cmd = CMD_INP;
	cmd->id_client = idClient;
	cmd->input = input;
	this->_queuedUDP.push_back(std::pair<void *, int>(cmd, sizeof(t_inp_client)));
}

void		Parser::addIDT(unsigned char idClient)
{
	t_idt_client	*cmd;

	std::cout << "Queued IDT" << std::endl;
	cmd = new t_idt_client;
	cmd->id_cmd = CMD_IDT;
	cmd->id_client = idClient;
	this->_queuedUDP.push_back(std::pair<void *, int>(cmd, sizeof(t_idt_client)));
}
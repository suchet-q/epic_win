#include		"Game.h"


Game::Game(int id, std::list<Client *> &clients)
{
  this->_id = id;
  this->_clients = clients;
  this->_gameAttribut.initMutex();
  this->_gameClient.initMutex();
  this->_gameSocket.initMutex();
  this->_isInit = false;
}

Game::Game() {}

Game::~Game() {}



std::list<Client *>&	Game::getClients() {
  return this->_clients;
}

MetaSocket<>&		Game::getSocket() {
  return this->_socketUDP;
}

int			Game::getID() {
  return (this->_id);
}

ResourcesGame&		Game::getResources() {
  return (this->_resources);
}

bool			Game::getIsInit() const {
  return this->_isInit;
}



void			Game::setID(int id) {
  this->_id = id;
}

void			Game::setResources(ResourcesGame const &resources) {
  this->_resources = resources;
}



bool			Game::lockClient() {
  return this->_gameClient.Lock();
}

bool			Game::unlockClient() {
  return this->_gameClient.Unlock();
}

bool			Game::lockSocket() {
  return this->_gameSocket.Lock();
}

bool			Game::unlockSocket() {
  return this->_gameSocket.Unlock();
}

bool		Game::init()
{
	t_stl_server	rep;
	struct sockaddr_in sin;
	socklen_t len = sizeof(sin);
	t_cmd			cmd;

	std::cout << "Initializing UDP Socket in Game " << this->_id << std::endl;
	this->_socketUDP.init(UDP);
	this->_socketUDP.Bind("127.0.0.1", 0);
	getsockname(this->_socketUDP.getSocket(), (struct sockaddr *)&sin, &len);
	std::cout << "Socket binded on port number " << ntohs(sin.sin_port) << std::endl;
	rep.id_command = 6;
	rep.response = 1;
	rep.port = ntohs(sin.sin_port);
	memcpy(cmd.cmd, &rep, sizeof(rep));
	cmd.size = sizeof(rep);
	std::cout << "size de la reponse : " << sizeof(rep) << std::endl;
	this->lockClient();
	for (std::list<Client *>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it)\
		(*it)->getWriteBuffer()->push_back(cmd);
	this->unlockClient();
	this->_isInit = true;
	return true;
}

bool			Game::lockAttribut() {
  return this->_gameAttribut.Lock();
}

bool			Game::unlockAttribut() {
  return this->_gameAttribut.Unlock();
}



void			Game::initPlayersShip()
{
  unsigned int		type = PLAYER1;

  for (std::list<Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
    _resources.createShip();
    _resources.getShipList().back()->setType(static_cast<entityType>(type));
    _clientToShip[*it] = _resources.getShipList().back();
    type++;
  }
/*	while (readyClients < this->_clients.size())
	{
		for (std::list<Client *>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it)
		{
			this->lockClient();
			if ((*it)->getFrameCMD().cmd.size == 2 /*&& (*it)->getFrameCMD().cmd.cmd[0] == 15*/ /* need macro omg *//*)
			{
				memcpy(&(*it)->getUDPsin(), &(*it)->getFrameCMD().sin, sizeof(struct sockaddr_in));
				++readyClients;
			}
			this->unlockClient();
		}
	}*/
}

bool			Game::launchThread(void *arg) {
  return this->_thread.start(&Game::startGame, this, arg);
}

void			Game::waitAllClients()
{
  unsigned char	readyClients = 0;

  while (readyClients < this->_clients.size())
    {
      for (std::list<Client *>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it)
	{
	  this->lockClient();
	  if ((*it)->getFrameCMD().cmd.size == 2 && (*it)->getFrameCMD().cmd.cmd[0] == 15 /* need macro omg */)
	    {
	      memcpy(&(*it)->getUDPsin(), &(*it)->getFrameCMD().sin, sizeof(struct sockaddr_in));
	      ++readyClients;
	    }
	  this->unlockClient();
	}
    }
}

int			Game::startGame(void *var)
{
  std::cout << "j'ai lance la game ma gueule" << std::endl;
  this->init();
  std::cout << "J'attend tout les clients ma gueule" << std::endl;
  this->waitAllClients();
  std::cout << "Tout les clients sont pr�sents ma gueue !" << std::endl;

  /*identification verifier nchanger status dans infos client puis lancer la game*/
  /*appel de methode init etc... et la loop de la game*/
  std::cout << "c'est la fin de la game maggle" << std::endl;
  while(true);
  return (1);
}

void			Game::manageClientsInputs()
{
  t_inp_client		cmd;

  for (std::map<Client*, Ship*>::iterator it = _clientToShip.begin();
       it != _clientToShip.end(); ++it)
    if (!(*it).first->getFrameCMD().cmd.size) {
      memcpy(&cmd, (*it).first->getFrameCMD().cmd.cmd, sizeof(t_inp_client));
      if (cmd.id_cmd = 14) //TODO : MACRO
	(*it).second->manageInput(cmd.input);
  }
}

void			Game::loop()
{
 
}
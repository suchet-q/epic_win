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

std::map<entityType, t_tab_hit_box> *Game::getTabHitBox() const
{
	return this->_tabHitBox;
}

void				Game::setTabHitBox(std::map<entityType, t_tab_hit_box> &tab)
{
	this->_tabHitBox = &tab;
}

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


std::map<entityType, LoadLib<> *> Game::getInstanceGetter() const
{
	return this->_instanceGetter;
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

bool		Game::loadAllLib()
{
	this->_instanceGetter[DRONE] = new LoadLib<>;
	this->_instanceGetter[DRONE]->loadLibrary("libDrone");

	this->_instanceGetter[ALIEN] = new LoadLib<>;
	this->_instanceGetter[ALIEN]->loadLibrary("libAlien");

	this->_instanceGetter[DOG] = new LoadLib<>;
	this->_instanceGetter[DOG]->loadLibrary("libDog");

	this->_instanceGetter[JUMPER] = new LoadLib<>;
	this->_instanceGetter[JUMPER]->loadLibrary("libJumper");

	this->_instanceGetter[XWING] = new LoadLib<>;
	this->_instanceGetter[XWING]->loadLibrary("libXwing");

	this->_instanceGetter[METROID] = new LoadLib<>;
	this->_instanceGetter[METROID]->loadLibrary("libMetroid");

	return true;
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
	this->loadAllLib();
	this->initBufClient();
	this->initPlayersShip();
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

void			Game::initBufClient()
{
	t_rep_client	tmp;

	memset(&tmp, 0, sizeof(t_rep_client));
	tmp.size = 0;
	std::cout << "la size elle est a 0 maggle" << std::endl;
	tmp.life = 3;
	tmp.weapon = MISSIL;
	tmp.bonus = false;
	tmp.score = 0;
	tmp.hightScore = 0;
	tmp.status = EMPTY;
	std::list<Client *>::iterator it = this->_clients.begin();
	for (; it != this->_clients.end(); ++it)
	{
		memcpy(&this->_repClient[(*it)], &tmp, sizeof(tmp));
//		this->_repClient[(*it)] = tmp;
	}
}

void			Game::initPlayersShip()
{
  unsigned int		type = PLAYER1;

  for (std::list<Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it) 
  {
    _resources.createPlayerShip();
	_resources.getShipList().back()->getFloatCoord().setX(30);
	_resources.getShipList().back()->getFloatCoord().setY((768 - 100) / (_clients.size() + 1) * type);
	_resources.getShipList().back()->setType(static_cast<entityType>(type));
    _resources.getShipList().back()->setEntitiesPool(_resources.getEntitiesPool());
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
		  system("pause");
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
  std::cout << "Tout les clients sont présents ma gueue !" << std::endl;
  this->loop();
  /*identification verifier changer status dans infos client puis lancer la game*/
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
  {
	  if ((*it).first->getFrameCMD().cmd.size) {
		  memcpy(&cmd, (*it).first->getFrameCMD().cmd.cmd, sizeof(t_inp_client));
		  if (cmd.id_cmd == 14) //TODO : MACRO
		  {
	//		  std::cout << "J'AI SET L'INPUT MAGGEEEEEEEEEEEEEEEEEEEUL" << std::endl;
			  (*it).second->setInput(cmd.input);
		  }

	  }
	  (*it).first->getFrameCMD().cmd.size = 0;
  }
}

void			Game::loop()
{
  std::map<Client *, t_rep_client>::iterator	itRep;
  std::list<Entity *>::iterator	itEntity;
  Coord<>		tmp;
  t_aff_server		affServer;
  t_evt_server		evtServer;
  t_scr_server		srcServer;
  t_lif_server		lifServer;
  int			nbUpdate;
  unsigned long int	ellapsedTime = 0;


  _clock.start();
  while (true)
    {
      ellapsedTime += _clock.elapsedTime();
      nbUpdate = ellapsedTime / REFRESH_TIME;

      this->manageClientsInputs();
      /*plus tard*//*update AI*/
      itEntity = this->_resources.getEntityList().begin();
      for (; itEntity != this->_resources.getEntityList().end(); ++itEntity)
		{
			tmp = (*itEntity)->getCoord();
			if (tmp.getX() < 0 || tmp.getX() > 1024)
			{
				itEntity = this->_resources.getEntityList().erase(itEntity);
				if (itEntity == this->_resources.getEntityList().end())
					break;
				tmp = (*itEntity)->getCoord();
			}

			for (int i = 0; i < nbUpdate; ++i)
				(*itEntity)->update(this->_resources.getEntityList());

			if (nbUpdate)
			{
				itRep = this->_repClient.begin();
				for (; itRep != this->_repClient.end(); ++itRep)
				{
					affServer.id_cmd = 10;
					affServer.type = (*itEntity)->getType();
					affServer.id_obj = 007/*mettre l id dans la class entity*/;
					affServer.x = tmp.getX();
					affServer.y = tmp.getY();
					memcpy(&(*itRep).second.buffer[(*itRep).second.size], &affServer, sizeof(affServer));
					(*itRep).second.size += sizeof(affServer);
				}
			}
		}

	  if (nbUpdate)
	  {

		  itRep = this->_repClient.begin();
		  for (; itRep != this->_repClient.end(); ++itRep)
		  {
			  /*info a mettre dans dans la map et retire la struc infoclient du client*/
			  srcServer.id_cmd = 11;
			  srcServer.score = (*itRep).second.score;
			  memcpy(&(*itRep).second.buffer[(*itRep).second.size], &srcServer, sizeof(srcServer));
			  (*itRep).second.size += sizeof(srcServer);
			  lifServer.id_cmd = 12;
			  lifServer.life = (*itRep).second.life;
			  memcpy(&(*itRep).second.buffer[(*itRep).second.size], &lifServer, sizeof(lifServer));
			  (*itRep).second.size += sizeof(lifServer);

				std::cout << "sending buffer of size " << (*itRep).second.size << " to client " << (*itRep).first->getID() << " on port " << ntohs((*itRep).first->getUDPsin().sin_port) << std::endl;
				this->_socketUDP.sendTo(static_cast<void *>((*itRep).second.buffer),
					  (*itRep).second.size, &(*itRep).first->getUDPsin());
				(*itRep).second.size = 0;
		  }

		}
      
	ellapsedTime %= REFRESH_TIME;

      /*check colision peut etre fait dans update entity (vie ou mort)*/
      /*evtServer.id_cmd = 13; set levent (mort colision etc..) surment pas fait ici
	evtServer.event = ;*/
    }
}

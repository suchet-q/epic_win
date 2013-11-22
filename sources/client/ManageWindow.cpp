#include "ManageWindow.h"

Managewindow::Managewindow(sf::RenderWindow *window, sf::Mutex *mutex)
{
  this->_Mutex = mutex;
  this->Window = window;
  this->_Drawer = new Drawer(window, mutex);
  fct = new pfObject[19];
  fct[0] = &Managewindow::GetPoolDrone;
  fct[1] = &Managewindow::GetPoolAlien;
  fct[2] = &Managewindow::GetPoolDog;
  fct[3] = &Managewindow::GetPoolJumper;
  fct[4] = &Managewindow::GetPoolXwing;
  fct[5] = &Managewindow::GetPoolMetroid;
  fct[6] = &Managewindow::GetPoolLarve;
  fct[7] = &Managewindow::GetPoolFireball;
  fct[8] = &Managewindow::GetPoolMissil;
  fct[9] = &Managewindow::GetPoolBalls;
  fct[10] = &Managewindow::GetPoolExplosion;
  fct[11] = &Managewindow::GetPoolMissil2;
  fct[12] = &Managewindow::GetPoolMissil3;
  fct[13] = &Managewindow::GetPoolMissil4;
  fct[14] = &Managewindow::GetPoolLaser;
  fct[15] = &Managewindow::GetPoolDecor1Top;
  fct[16] = &Managewindow::GetPoolDecor1Down;
  fct[17] = &Managewindow::GetPoolDecor2Top;
  fct[18] = &Managewindow::GetPoolDecor2Down;

  fct2 = new pfPool[19];
  fct2[0] = &Managewindow::BackPoolDrone;
  fct2[1] = &Managewindow::BackPoolAlien;
  fct2[2] = &Managewindow::BackPoolDog;
  fct2[3] = &Managewindow::BackPoolJumper;
  fct2[4] = &Managewindow::BackPoolXwing;
  fct2[5] = &Managewindow::BackPoolMetroid;
  fct2[6] = &Managewindow::BackPoolLarve;
  fct2[7] = &Managewindow::BackPoolFireball;
  fct2[8] = &Managewindow::BackPoolMissil;
  fct2[9] = &Managewindow::BackPoolBalls;
  fct2[10] = &Managewindow::BackPoolExplosion;
  fct2[11] = &Managewindow::BackPoolMissil2;
  fct2[12] = &Managewindow::BackPoolMissil3;
  fct2[13] = &Managewindow::BackPoolMissil4;
  fct2[14] = &Managewindow::BackPoolLaser;  
  fct2[15] = &Managewindow::BackPoolDecor1Top;
  fct2[16] = &Managewindow::BackPoolDecor1Down;
  fct2[17] = &Managewindow::BackPoolDecor2Top;
  fct2[18] = &Managewindow::BackPoolDecor2Down;
}

Managewindow::~Managewindow()
{

}

bool	Managewindow::InitDrawer()
{
  if ((this->_Drawer->InitSprite()) == false)
    return false;
  return true;
}

void	Managewindow::Update()
{
  bool tmp;
  for(std::list<Entity *>::iterator it = this->_EntityList.begin(); it != this->_EntityList.end();)
    {
      tmp = false;
      if ((*it)->getEtat() == 1)
	this->_Drawer->drowSprite((*it)->getType() - 1, (*it)->getX(), (*it)->getY(), (*it)->getStatus());
      else
	{
	  if ((*it)->getEtat() == 2 && (*it)->SpriteAlive() == true)
	    {
	      this->_Drawer->drowSprite(14, (*it)->getX(), (*it)->getY(), (*it)->getStatus());
	      (*it)->GetSprite((*it)->getX(), (*it)->getY(), 10, N);
	    }
	  else if ((*it)->getEtat() == 2 && (*it)->SpriteAlive() == false)
	    {
	      this->BackInPool((*it)->getType() - 5, *it);
	      it = this->_EntityList.erase(it);
	      tmp = true;
	    }
	}
      if (it != this->_EntityList.end() && tmp == false)
	++it;
    }
  for(std::list<Ship *>::iterator it = this->_ShipList.begin(); it != this->_ShipList.end();)
    {
      tmp = false;
      if ((*it)->GetEtat() == 1)
	this->_Drawer->drowSprite((*it)->GetTeam() - 1, (*it)->getX(), (*it)->getY(), (*it)->GetStatus());
      else
	{
	  if ((*it)->GetEtat() == 2 && (*it)->SpriteAlive() == true)
	    {
	      this->_Drawer->drowSprite(14, (*it)->getX(), (*it)->getY(), (*it)->GetStatus());
	      (*it)->GetSprite((*it)->getX(), (*it)->getY(), NOTHING, 10, N);
	    }
	  else if ((*it)->GetEtat() == 2 && (*it)->SpriteAlive() == false)
	    {
	      delete (*it);
	      it = this->_ShipList.erase(it);
	      tmp = true;
	    }
	}
      if (it != this->_ShipList.end() && tmp == false)
	++it;
    }
}

void	Managewindow::SetInputs(Ship *ship, unsigned short y)
{
  if (y < ship->getY())
    ship->setInput(TOP);
  else if (y > ship->getY())
    ship->setInput(DOWN);
  else
    ship->setInput(LEFT);
}

void	Managewindow::SetShip(unsigned short id_obj, unsigned short x, unsigned short y, unsigned char type)
{
  for (std::list<Ship *>::iterator it = this->_ShipList.begin(); it != this->_ShipList.end(); ++it)
    {
      if ((*it)->getId() == id_obj)
	{
	      this->SetInputs(*it, y);
	      (*it)->GetSprite(x, y, (*it)->getInput(), 10, N);
	      return;
	}
    }
  Ship	*tmp = new Ship(x, y, (int)type, id_obj);
  tmp->GetSprite(x, y, NOTHING, 10, N);
  this->_ShipList.push_back(tmp);
  return;
}

void	Managewindow::SetEntity(unsigned short id_obj, unsigned short x, unsigned short y, unsigned char type)
{
  for (std::list<Entity *>::iterator it = this->_EntityList.begin(); it != this->_EntityList.end(); ++it)
	{
	  if ((*it)->getId() == id_obj)
	    {
	      (*it)->GetSprite(x, y, 10, N);
	      return;
	    }
	}
  Entity	*tmp = this->GetInPool((int)type - 6);
  tmp->setId(id_obj);
  tmp->GetSprite(x, y, 10, N);
  this->_EntityList.push_back(tmp);
  return;
}

void	Managewindow::SetItem(unsigned char type, unsigned short id_obj, unsigned short x, unsigned short y)
{
  if (type >= 1 && type <= 4)
    {
      this->SetShip(id_obj, x, y, type);
    }
  else if (type == 5)
    {
      this->SetDeath(id_obj, x, y);
    }
  else
    {
      this->SetEntity(id_obj, x, y, type);
    }
}

void	Managewindow::SetDeath(unsigned short id_obj, unsigned short x, unsigned short y)
{
  for (std::list<Entity *>::iterator it = this->_EntityList.begin(); it != this->_EntityList.end(); ++it)
    {
      if ((*it)->getId() == id_obj)
	{
	  (*it)->GetSprite(x, y, 0, DEAD);
	  return;
	}
    }

  for (std::list<Ship *>::iterator it = this->_ShipList.begin(); it != this->_ShipList.end(); ++it)
    {
      if ((*it)->getId() == id_obj)
  	{
  	  (*it)->GetSprite(x, y, NOTHING,0, DEAD);
  	  return;
  	}
    }
  return;
}

void	Managewindow::BackInPool(int type, Entity *entity)
{
  (this->*fct2[type])(entity);
}

void	Managewindow::BackPoolExplosion(Entity *entity)
{
  entity = entity;
}

void	Managewindow::BackPoolDrone(Entity *entity)
{
  entity->ResetData();
  this->_DronePool.freeInstance(dynamic_cast<Drone*>(entity));
}

void	Managewindow::BackPoolDecor1Top(Entity *entity)
{
  entity->ResetData();
  this->_Decor1TopPool.freeInstance(dynamic_cast<Decor1top*>(entity));
}

void	Managewindow::BackPoolDecor1Down(Entity *entity)
{
  entity->ResetData();
  this->_Decor1DownPool.freeInstance(dynamic_cast<Decor1down*>(entity));
}

void	Managewindow::BackPoolDecor2Top(Entity *entity)
{
  entity->ResetData();
  this->_Decor2TopPool.freeInstance(dynamic_cast<Decor2top*>(entity));
}

void	Managewindow::BackPoolDecor2Down(Entity *entity)
{
  entity->ResetData();
  this->_Decor2DownPool.freeInstance(dynamic_cast<Decor2down*>(entity));
}

void	Managewindow::BackPoolAlien(Entity *entity)
{
  entity->ResetData();
  this->_AlienPool.freeInstance(dynamic_cast<Alien*>(entity));
}

void	Managewindow::BackPoolDog(Entity *entity)
{
  entity->ResetData();
  this->_DogPool.freeInstance(dynamic_cast<Dog*>(entity));
}

void	Managewindow::BackPoolJumper(Entity *entity)
{
  entity->ResetData();
  this->_JumperPool.freeInstance(dynamic_cast<Jumper*>(entity));
}

void	Managewindow::BackPoolXwing(Entity *entity)
{
  entity->ResetData();
  this->_XwingPool.freeInstance(dynamic_cast<Xwing*>(entity));
}

void	Managewindow::BackPoolMetroid(Entity *entity)
{
  entity->ResetData();
  this->_MetroidPool.freeInstance(dynamic_cast<Metroid*>(entity));
}

void	Managewindow::BackPoolLarve(Entity *entity)
{
  entity->ResetData();
  this->_LarvePool.freeInstance(dynamic_cast<Larve*>(entity));
}

void	Managewindow::BackPoolLaser(Entity *entity)
{
  entity->ResetData();
  this->_LaserPool.freeInstance(dynamic_cast<Laser*>(entity));
}
void	Managewindow::BackPoolFireball(Entity *entity)
{
  entity->ResetData();
  this->_FireballPool.freeInstance(dynamic_cast<Fireball*>(entity));
}

void	Managewindow::BackPoolMissil(Entity *entity)
{
  entity->ResetData();
  this->_MissilPool.freeInstance(dynamic_cast<Missil*>(entity));
}

void	Managewindow::BackPoolBalls(Entity *entity)
{
  entity->ResetData();
  this->_BallsPool.freeInstance(dynamic_cast<Balls*>(entity));
}

void	Managewindow::BackPoolMissil2(Entity *entity)
{
  entity->ResetData();
  this->_Missil2Pool.freeInstance(dynamic_cast<Missil2*>(entity));
}

void	Managewindow::BackPoolMissil3(Entity *entity)
{
  entity->ResetData();
  this->_Missil3Pool.freeInstance(dynamic_cast<Missil3*>(entity));
}

void	Managewindow::BackPoolMissil4(Entity *entity)
{
  entity->ResetData();
  this->_Missil4Pool.freeInstance(dynamic_cast<Missil4*>(entity));
}


Entity	*Managewindow::GetInPool(unsigned char type)
{
  return (this->*fct[(int)type])();
}

Entity *Managewindow::GetPoolDrone()
{
  return(this->_DronePool.getInstance());
}

Entity		*Managewindow::GetPoolExplosion()
{
  return(this->_AlienPool.getInstance());
}

Entity		*Managewindow::GetPoolAlien()
{
  return(this->_AlienPool.getInstance());
}

Entity		*Managewindow::GetPoolDog()
{
  return (this->_DogPool.getInstance());
}

Entity		*Managewindow::GetPoolJumper()
{
  return (this->_JumperPool.getInstance());
}

Entity		*Managewindow::GetPoolXwing()
{
  return (this->_XwingPool.getInstance());
}

Entity		*Managewindow::GetPoolMetroid()
{
  return (this->_MetroidPool.getInstance());;
}

Entity		*Managewindow::GetPoolLarve()
{
  return (this->_LarvePool.getInstance());
}

Entity		*Managewindow::GetPoolFireball()
{
  return (this->_FireballPool.getInstance());
}

Entity		*Managewindow::GetPoolMissil()
{
  return (this->_MissilPool.getInstance());
}

Entity		*Managewindow::GetPoolBalls()
{
  return (this->_BallsPool.getInstance());
}

Entity		*Managewindow::GetPoolMissil2()
{
  return (this->_Missil2Pool.getInstance());
}

Entity		*Managewindow::GetPoolMissil3()
{
  return (this->_Missil3Pool.getInstance());
}

Entity	       *Managewindow::GetPoolMissil4()
{
  return (this->_Missil4Pool.getInstance());
}

Entity	       *Managewindow::GetPoolDecor1Top()
{
  return (this->_Decor1TopPool.getInstance());
}

Entity	       *Managewindow::GetPoolDecor1Down()
{
  return (this->_Decor1DownPool.getInstance());
}

Entity	       *Managewindow::GetPoolDecor2Top()
{
  return (this->_Decor2TopPool.getInstance());
}

Entity	       *Managewindow::GetPoolDecor2Down()
{
  return (this->_Decor2DownPool.getInstance());
}

Entity	       *Managewindow::GetPoolLaser()
{
  return (this->_LaserPool.getInstance());
}

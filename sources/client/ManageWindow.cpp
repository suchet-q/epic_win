#include "ManageWindow.h"

Managewindow::Managewindow(sf::RenderWindow *window)
{
  this->Window = window;
  this->_Drawer = new Drawer(window);
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

void	Managewindow::Update(float elapsed)
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
	      (*it)->GetSprite((*it)->getX(), (*it)->getY(), /*elapsed*/10, N);
	    }
	  else if ((*it)->getEtat() == 2 && (*it)->SpriteAlive() == false)
	    {
	      delete (*it);
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
	this->_Drawer->drowSprite((*it)->getType() - 1, (*it)->getX(), (*it)->getY(), (*it)->GetStatus());
      else
	{
	  if ((*it)->GetEtat() == 2 && (*it)->SpriteAlive() == true)
	    {
	      this->_Drawer->drowSprite(14, (*it)->getX(), (*it)->getY(), (*it)->GetStatus());
	      (*it)->GetSprite((*it)->getX(), (*it)->getY(), NOTHING, /*elapsed*/10, N);
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
  Ship	*tmp = new Ship(x, y, type, id_obj);
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
  Entity	*tmp = this->_SpriteBank.GetObject(static_cast<int>(type) - 6, id_obj);
  tmp->GetSprite(x, y, 10, N);
  this->_EntityList.push_back(tmp);
  return;
}

void	Managewindow::SetItem(unsigned char type, unsigned short id_obj, unsigned short x, unsigned short y)
{
  if (type >= 1 && type <= 4)
    this->SetShip(id_obj, x, y, type);
  else if (type == 5)
    this->SetDeath(id_obj, x, y);
  else
      this->SetEntity(id_obj, x, y, type);
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
  	  // this->_EntitySpriteList.push_back((*it)->GetSprite(x, y, 0, DEAD));
  	  (*it)->GetSprite(x, y, NOTHING,0, DEAD);
  	  return;
  	}
    }
  return;
}


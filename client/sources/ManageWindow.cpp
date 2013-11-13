#include "ManageWindow.h"

Managewindow::Managewindow(sf::RenderWindow *window)
{
  this->Window = window;
  this->_SpriteBank.SetImg();
}

Managewindow::~Managewindow()
{

}

void	Managewindow::Update()
{
  for (std::list<sf::Sprite>::iterator it = this->_EntitySpriteList.begin(); it != this->_EntitySpriteList.end();)
    {
      this->Window->Draw(*it);
      it = this->_EntitySpriteList.erase(it);
      if (it != this->_EntitySpriteList.end())
	++it;
    }
  for (std::list<sf::Sprite>::iterator it = this->_ShipSpriteList.begin(); it != this->_ShipSpriteList.end();)
    {
      this->Window->Draw(*it);
      it = this->_EntitySpriteList.erase(it);
      if (it != this->_EntitySpriteList.end())
	++it;
    }
  return;
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

void	Managewindow::SetEntity(unsigned short id_obj, unsigned short x, unsigned short y, unsigned char type)
{
  for (std::list<Entity *>::iterator it = this->_EntityList.begin(); it != this->_EntityList.end(); ++it)
	{
	  if ((*it)->getId() == id_obj)
	    {
	      this->_EntitySpriteList.push_back((*it)->GetSprite(x, y, 10, N));
	      return;
	    }
	}
  Entity	*tmp = this->_SpriteBank.GetObject(type - 6, id_obj);
  this->_EntitySpriteList.push_back(tmp->GetSprite(x, y, 10, N));
  this->_EntityList.push_back(tmp);
  return;
}

void	Managewindow::SetShip(unsigned short id_obj, unsigned short x, unsigned short y)
{
  for (std::list<Ship *>::iterator it = this->_ShipList.begin(); it != this->_ShipList.end(); ++it)
    {
      if ((*it)->getId() == id_obj)
	{
	  if ((*it)->SpriteAlive() == true)
	    {
	      this->SetInputs(*it, y);
	      this->_ShipSpriteList.push_back((*it)->GetSprite(x, y, (*it)->getInput(), 10, N));
	    }
	  else
	    this->_ShipList.erase(it);
	  return;
	}
    }
  Ship	*tmp = new Ship(x, y, id_obj, id_obj);
  this->_ShipSpriteList.push_back(tmp->GetSprite(x, y, NOTHING, 10, N));
  this->_ShipList.push_back(tmp);
  return;
}

void	Managewindow::SetDeath(unsigned short id_obj, unsigned short x, unsigned short y)
{
  for (std::list<Entity *>::iterator it = this->_EntityList.begin(); it != this->_EntityList.end(); ++it)
	{
	  if ((*it)->getId() == id_obj)
	    {
	      this->_EntitySpriteList.push_back((*it)->GetSprite(x, y, 10, DEAD));
	      return;
	    }
	}
  for (std::list<Ship *>::iterator it = this->_ShipList.begin(); it != this->_ShipList.end(); ++it)
    {
      if ((*it)->getId() == id_obj)
	{
	  this->_ShipSpriteList.push_back((*it)->GetSprite(x, y, LEFT, 10, DEAD));
	  this->_ShipList.erase(it);
	  return;
	}
    }
}

void	Managewindow::SetExplosion()
{
  for (std::list<Entity *>::iterator it = this->_EntityList.begin(); it != this->_EntityList.end();)
    {
      if ((*it)->getEtat() == 2)
	{
	  if ((*it)->SpriteAlive() == true)
	    this->_EntitySpriteList.push_back((*it)->GetSprite(0, 0, 10, N));
	  else
	    {
	      it = this->_EntityList.erase(it);
	      //delete (*it);
	    }
	}
      if (it != this->_EntityList.end())
	++it;
    }
}

void	Managewindow::SetItem(unsigned char type, unsigned short id_obj, unsigned short x, unsigned short y)
{
  this->SetExplosion();
  if (type >= 1 && type <= 4)
    this->SetShip(id_obj, x, y);
  else if (type == 5)
    this->SetDeath(id_obj, x, y);
  else
    this->SetEntity(id_obj, x, y, type);
}

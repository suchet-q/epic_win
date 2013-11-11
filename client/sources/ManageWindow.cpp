#include "ManageWindow.h"

Managewindow::Managewindow(sf::RenderWindow *window)
{
  this->Window = window;
}

Managewindow::~Managewindow()
{

}

void	Managewindow::Update()
{
  for (std::list<sf::Sprite>::iterator it = this->_EntitySpriteList.begin(); it != this->_EntitySpriteList.end(); ++it)
    {
      this->Window->Draw(*it);
    }
  for (std::list<sf::Sprite>::iterator it2 = this->_ShipSpriteList.begin(); it2 != this->_ShipSpriteList.end(); ++it2)
    {
      this->Window->Draw(*it2);
    }
}

void	Managewindow::DrawSomething(unsigned short id, unsigned char type, unsigned short x, unsigned short y)
{
  if (type >= 1 && type <= 4)
    {
      for (std::list<Ship *>::iterator it = this->_ShipList.begin(); it != this->_ShipList.end(); ++it)
	{
	  if ((*it)->getId() == id)
	    {
	      if ((*it)->SpriteAlive() == true)
		this->_ShipSpriteList.push_back((*it)->GetSprite(x, y, /*INPUT*/LEFT, /*TIME*/10, N));
	      else
		this->_ShipList.erase(it);
	      return;
	    }
	}
      Ship	*tmp = new Ship(x, y, (int)type, id);
      this->_ShipSpriteList.push_back(tmp->GetSprite(x, y, NOTHING, /*TIME*/10, N));
      this->_ShipList.push_back(tmp);
      return;
    }
  else
    {
      for (std::list<Entity *>::iterator it = this->_EntityList.begin(); it != this->_EntityList.end(); ++it)
	{
	  if ((*it)->getId() == id)
	    {
	      if ((*it)->SpriteAlive() == true)
		this->_EntitySpriteList.push_back((*it)->GetSprite(x, y, /*TIME*/10, N));
	      else
		this->_EntityList.erase(it);
	      return;
	    }
	}
      Entity	*tmp = this->_SpriteBank.GetObject(type, id);
      this->_EntitySpriteList.push_back(tmp->GetSprite(x, y, /*TIME*/10, N));
      this->_EntityList.push_back(this->_SpriteBank.GetObject(type, id));
      return;
    }
  return;
}

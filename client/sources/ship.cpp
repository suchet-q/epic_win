//
// ship.cpp for ship in /home/heuzey_m//TEK3/R-TYPE
// 
// Made by mathieu heuzey
// Login   <heuzey_m@epitech.net>
// 
// Started on  Sat Oct 26 23:30:25 2013 mathieu heuzey
// Last update Tue Nov 12 03:17:51 2013 mathieu heuzey
//

#include "ship.h"

Ship::Ship(int x, int y, int team, int id)
{
  // this->SetSprite();
  this->_Status = 3;
  this->_Team = team;
  this->_Width = 33.2;
  this->_Height = 17.2;
  this->_TotalWidth = 166;
  this->_TotalHeight = 86;
  this->_EllapsedTime = FRAMETIME;
  this->_FrameTime = FRAMETIME;
  this->_Type = 1;
  this->_Id = id;
  this->_Old = 1;
  this->_X = x;
  this->_Y = y;
  this->_Inputs = NOTHING;
}

bool		Ship::SpriteAlive()
{
  if (this->_Old == 0)
    return (false);
  return (true);
}

Ship::~Ship()
{

}

bool	Ship::SetSprite()
{
  if (this->_TmpImg.LoadFromFile("./sprites/r-typesheet42.png"))
    {
      this->_ShipSprite.SetImage(this->_TmpImg);
      return (true);
    }
  else
    return (false);
}

sf::Image	Ship::GetImg()
{
  return (this->_TmpImg);
}

sf::Sprite	Ship::GetSprite(int x, int y, Inputs inp, int time, Move move)
{
  this->_EllapsedTime += time;
  if (move == DEAD)
    this->_Old = 0;
  if (this->_EllapsedTime >= this->_FrameTime)
    {
      this->CheckInputs(inp);
      this->_ShipSprite.SetPosition(x, y);
      this->_EllapsedTime = 0;
      return (this->_ShipSprite);
    }
  return (this->_ShipSprite);
}

void	Ship::CheckLeftAndRight(std::pair<int, int> tmp)
{
  switch(this->_Status)
    {
    case 1:
      {
	this->_ShipSprite.SetSubRect(sf::IntRect(this->_Width * 2, this->_Height * tmp.first, this->_Width * 3 , this->_Height * tmp.second  ));
	this->_Status = 0;
	break;
      }
    case 3:
      {
	this->_ShipSprite.SetSubRect(sf::IntRect(this->_Width * 2, this->_Height * tmp.first, this->_Width * 3 , this->_Height * tmp.second  ));
	this->_Status = 0;
	break;
      }
    case 2:
      {
	this->_Status = 1;
	this->_ShipSprite.SetSubRect(sf::IntRect(this->_Width * 3, this->_Height * tmp.first, this->_Width * 4, this->_Height * tmp.second  ));
	break;
      }
    case 4:
      {
	this->_Status = 3;
	this->_ShipSprite.SetSubRect(sf::IntRect(this->_Width, this->_Height * tmp.first, this->_Width * 2, this->_Height * tmp.second  ));
	break;
      }
    default:
      {
	this->_ShipSprite.SetSubRect(sf::IntRect(this->_Width * 2, this->_Height * tmp.first, this->_Width * 3 , this->_Height * tmp.second  ));
      }
    }
}

void	Ship::CheckTop(std::pair<int, int> tmp)
{
  switch(this->_Status)
    {
    case 4:
      {
	this->_Status = 3;
	this->_ShipSprite.SetSubRect(sf::IntRect(this->_Width, this->_Height * tmp.first, this->_Width * 2, this->_Height * tmp.second  ));
	break;
      }
    case 3:
      {
	this->_Status = 0;
	this->_ShipSprite.SetSubRect(sf::IntRect(this->_Width * 2, this->_Height * tmp.first, this->_Width * 3 , this->_Height * tmp.second  ));
	break;
      }
    case 0:
      {
	this->_Status = 1;
	this->_ShipSprite.SetSubRect(sf::IntRect(this->_Width * 3, this->_Height * tmp.first, this->_Width * 4, this->_Height * tmp.second  ));
	break;
      }
    default:
      {
	this->_Status = 2;
	this->_ShipSprite.SetSubRect(sf::IntRect(this->_Width * 4, this->_Height * tmp.first, this->_TotalWidth , this->_Height * tmp.second  ));
      }
    }
}

void	Ship::CheckDown(std::pair<int, int> tmp)
{
  switch(this->_Status)
    {
    case 2:
      {
	this->_Status = 1;
	this->_ShipSprite.SetSubRect(sf::IntRect(this->_Width * 3, this->_Height * tmp.first, this->_Width * 4, this->_Height * tmp.second  ));
	break;
      }
    case 1:
      {
	this->_Status = 0;
	this->_ShipSprite.SetSubRect(sf::IntRect(this->_Width * 2, this->_Height * tmp.first, this->_Width * 3 , this->_Height * tmp.second  ));
	break;
      }
    case 0:
      {
	this->_Status = 3;
	this->_ShipSprite.SetSubRect(sf::IntRect(this->_Width, this->_Height * tmp.first, this->_Width * 2, this->_Height * tmp.second  ));
	break;
      }
    default:
      {
	this->_Status = 4;
	this->_ShipSprite.SetSubRect(sf::IntRect(0, this->_Height * tmp.first, this->_Width , this->_Height * tmp.second  ));
      }
    }
}

void	Ship::CheckNothing(std::pair<int, int> tmp)
{
  switch(this->_Status)
    {
    case 1:
      {
	this->_Status = 0;
	this->_ShipSprite.SetSubRect(sf::IntRect(this->_Width * 2, this->_Height * tmp.first, this->_Width * 3 , this->_Height * tmp.second  ));
	break;
      }
    case 2:
      {
	this->_Status = 1;
	this->_ShipSprite.SetSubRect(sf::IntRect(this->_Width * 3, this->_Height * tmp.first, this->_Width * 4, this->_Height * tmp.second  ));
	break;
      }
    case 3:
      {
	this->_Status = 0;
	this->_ShipSprite.SetSubRect(sf::IntRect(this->_Width * 2, this->_Height * tmp.first, this->_Width * 3 , this->_Height * tmp.second  ));
	break;
      }
    case 4:
      {
	this->_Status = 3;
	this->_ShipSprite.SetSubRect(sf::IntRect(this->_Width, this->_Height * tmp.first, this->_Width * 2, this->_Height * tmp.second  ));
	break;
      }
    }
}

void	Ship::CheckInputs(Inputs inp)
{
  std::map<int, std::pair<int, int> > m;
  std::pair<int, int> tmp;

  m.insert(std::make_pair(1, std::make_pair(0, 1)));
  m.insert(std::make_pair(2, std::make_pair(1, 2)));
  m.insert(std::make_pair(3, std::make_pair(2, 3)));
  m.insert(std::make_pair(4, std::make_pair(3, 4)));
  m.insert(std::make_pair(5, std::make_pair(4, 5)));
  tmp = m.find(this->_Team)->second;

  switch(inp) 
    {
    case LEFT:
      this->CheckLeftAndRight(tmp);
      break;
    case RIGHT: 
      this->CheckLeftAndRight(tmp);
      break; 
    case TOP:
      this->CheckTop(tmp);
      break;
    case DOWN: 
      this->CheckDown(tmp);
      break;
    case NOTHING:
      this->CheckNothing(tmp);
    }
}

unsigned char Ship::getType()
{
  return (this->_Type);
}

int		Ship::getId()
{
  return (this->_Id);
}

int		Ship::getX()
{
  return (this->_X);
}

int		Ship::getY()
{
  return (this->_Y);
}

Inputs		Ship::getInput()
{
  return (this->_Inputs);
}

void		Ship::setInput(Inputs inp)
{
  this->_Inputs = inp;
}

#include "decor1top.h"

Decor1top::Decor1top()
{
  this->_Status = 1;
  this->_FrameTime = FRAMETIME;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 20;
}


Decor1top::~Decor1top()
{
}

void		Decor1top::ResetData()
{
  this->_Status = 1;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 20;
}

bool		Decor1top::SpriteAlive() const
{
  if (this->_Old == 0)
    return (false);
  return (true);
}

void		Decor1top::CheckEtat(Move move, int x, int y)
{
 if (move == DEAD && this->_Etat == 1)
    {
      this->_Etat = 2;
      this->_X = x;
      this->_Y = y;
    }
}

void		Decor1top::FirstState(int x, int y, int time)
{
  time = time;
  this->_X = x;
  this->_Y = y;
}

void		Decor1top::CheckSize(int time)
{
  time = time;
  this->_Old = 0;
  this->_Status = 1;
}
  
void	Decor1top::GetSprite(int x, int y, unsigned int time, Move move)
{
  if (this->_Etat == 1)
    this->CheckEtat(move,x ,y);
  if (this->_Etat == 1)
    this->FirstState(x, y, time);
  else
    this->CheckSize(time);
}

void	Decor1top::setX(int x)
{
  this->_X = x;
}

void	Decor1top::setY(int Y)
{
  this->_Y = Y;
}

int	Decor1top::getX() const
{
  return (this->_X);
}

int	Decor1top::getY() const 
{
  return (this->_Y);
}

int	Decor1top::getId() const
{
  return (this->_Id);
}

int Decor1top::getType() const
{
  return (this->_Type);
}

int	Decor1top::getEtat() const
{
  return (this->_Etat);
}

int	Decor1top::getStatus() const
{
  return (this->_Status);
}

void	Decor1top::setId(int id)
{
  this->_Id = id;
}

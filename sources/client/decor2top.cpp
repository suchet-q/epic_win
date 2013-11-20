#include "decor2top.h"

Decor2top::Decor2top()
{
  this->_Status = 1;
  this->_FrameTime = FRAMETIME;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 22;
}


Decor2top::~Decor2top()
{
}

void		Decor2top::ResetData()
{
  this->_Status = 1;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 22;
}

bool		Decor2top::SpriteAlive() const
{
  if (this->_Old == 0)
    return (false);
  return (true);
}

void		Decor2top::CheckEtat(Move move, int x, int y)
{
 if (move == DEAD && this->_Etat == 1)
    {
      this->_Etat = 2;
      this->_X = x;
      this->_Y = y;
    }
}

void		Decor2top::FirstState(int x, int y, int time)
{
  time = time;
  this->_X = x;
  this->_Y = y;
}

void		Decor2top::CheckSize(int time)
{
  time = time;
  this->_Old = 0;
  this->_Status = 1;
}
  
void	Decor2top::GetSprite(int x, int y, unsigned int time, Move move)
{
  if (this->_Etat == 1)
    this->CheckEtat(move,x ,y);
  if (this->_Etat == 1)
    this->FirstState(x, y, time);
  else
    this->CheckSize(time);
}

void	Decor2top::setX(int x)
{
  this->_X = x;
}

void	Decor2top::setY(int Y)
{
  this->_Y = Y;
}

int	Decor2top::getX() const
{
  return (this->_X);
}

int	Decor2top::getY() const 
{
  return (this->_Y);
}

int	Decor2top::getId() const
{
  return (this->_Id);
}

int Decor2top::getType() const
{
  return (this->_Type);
}

int	Decor2top::getEtat() const
{
  return (this->_Etat);
}

int	Decor2top::getStatus() const
{
  return (this->_Status);
}

void	Decor2top::setId(int id)
{
  this->_Id = id;
}

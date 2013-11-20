#include "decor2down.h"

Decor2down::Decor2down()
{
  this->_Status = 0;
  this->_FrameTime = FRAMETIME;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 23;
}


Decor2down::~Decor2down()
{
}

void		Decor2down::ResetData()
{
  this->_Status = 0;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 23;  
}
bool		Decor2down::SpriteAlive() const
{
  if (this->_Old == 0)
    return (false);
  return (true);
}

void		Decor2down::CheckEtat(Move move, int x, int y)
{
 if (move == DEAD && this->_Etat == 1)
    {
      this->_Etat = 2;
      this->_X = x;
      this->_Y = y;
    }
}

void		Decor2down::FirstState(int x, int y, int time)
{
  time = time;
  this->_X = x;
  this->_Y = y;
}

void		Decor2down::CheckSize(int time)
{
  time = time;
  this->_Old = 0;
  this->_Status = 0;
}  
void	Decor2down::GetSprite(int x, int y, unsigned int time, Move move)
{
  if (this->_Etat == 1)
    this->CheckEtat(move,x ,y);
  if (this->_Etat == 1)
    this->FirstState(x, y, time);
  else
    this->CheckSize(time);
}

void	Decor2down::setX(int x)
{
  this->_X = x;
}

void	Decor2down::setY(int Y)
{
  this->_Y = Y;
}

int	Decor2down::getX() const
{
  return (this->_X);
}

int	Decor2down::getY() const 
{
  return (this->_Y);
}

int	Decor2down::getId() const
{
  return (this->_Id);
}

int Decor2down::getType() const
{
  return (this->_Type);
}

int	Decor2down::getEtat() const
{
  return (this->_Etat);
}

int	Decor2down::getStatus() const
{
  return (this->_Status);
}

void	Decor2down::setId(int id)
{
  this->_Id = id;
}

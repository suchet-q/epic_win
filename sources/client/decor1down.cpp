#include "decor1down.h"

Decor1down::Decor1down()
{
  this->_Status = 0;
  this->_FrameTime = FRAMETIME;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 21;
}


Decor1down::~Decor1down()
{
}

void		Decor1down::ResetData()
{
  this->_Status = 0;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 21;  
}
bool		Decor1down::SpriteAlive() const
{
  if (this->_Old == 0)
    return (false);
  return (true);
}

void		Decor1down::CheckEtat(Move move, int x, int y)
{
 if (move == DEAD && this->_Etat == 1)
    {
      this->_Etat = 2;
      this->_X = x;
      this->_Y = y;
    }
}

void		Decor1down::FirstState(int x, int y, int time)
{
  time = time;
  this->_X = x;
  this->_Y = y;
}

void		Decor1down::CheckSize(int time)
{
  time = time;
  this->_Old = 0;
  this->_Status = 0;
}  
void	Decor1down::GetSprite(int x, int y, unsigned int time, Move move)
{
  if (this->_Etat == 1)
    this->CheckEtat(move,x ,y);
  if (this->_Etat == 1)
    this->FirstState(x, y, time);
  else
    this->CheckSize(time);
}

void	Decor1down::setX(int x)
{
  this->_X = x;
}

void	Decor1down::setY(int Y)
{
  this->_Y = Y;
}

int	Decor1down::getX() const
{
  return (this->_X);
}

int	Decor1down::getY() const 
{
  return (this->_Y);
}

int	Decor1down::getId() const
{
  return (this->_Id);
}

int Decor1down::getType() const
{
  return (this->_Type);
}

int	Decor1down::getEtat() const
{
  return (this->_Etat);
}

int	Decor1down::getStatus() const
{
  return (this->_Status);
}

void	Decor1down::setId(int id)
{
  this->_Id = id;
}

#include "metroid.h"

Metroid::Metroid(int id)
{
  this->_Status = 1;
  this->_Id = id;
  this->_FrameTime = FRAMETIME;
  this->_Old = 1;
  this->_Etat = 1;
  this->_Size = 3;
  this->_EllapsedTime = 0;
  this->_Type = 10;
}

Metroid::~Metroid()
{  
}

bool		Metroid::SpriteAlive() const
{
  if (this->_Old == 0)
    return (false);
  return (true);
}

void		Metroid::CheckEtat(Move move, int x, int y)
{
 if (move == DEAD && this->_Etat == 1)
    {
      this->_Etat = 2;
      if (this->_Size == 1)
	this->_Status = 8;
      else if(this->_Size == 2)
	this->_Status = 4;
      else
	this->_Status = 0;
      this->_X = x;
      this->_Y = y;
    }
}

void		Metroid::FirstState(int x, int y, int time)
{
  this->_X = x;
  this->_Y = y;  
  this->_EllapsedTime += time;
  if (this->_EllapsedTime >= this->_FrameTime)
    {
      if (this->_Status == 4)
	this->_Status = -1;
      this->_Status += 1;
      this->_EllapsedTime = 0;
    }
}


void		Metroid::CheckSize(int time)
{
  this->_EllapsedTime += time;
  switch (this->_Size)
    {
    case 1:
      {
	if (this->_EllapsedTime >= this->_FrameTime)
	  {
	    if (this->_Status == 11)
	      this->_Old = 0;
	    this->_Status += 1;
	    this->_EllapsedTime = 0;
	  }
      }
    case 2:
      {
	if ( this->_EllapsedTime >= this->_FrameTime)
	  {
	    if (this->_Status == 6)
	      this->_Old = 0;
	    this->_Status += 1;
	    this->_EllapsedTime = 0;
	  }
      }
    case 3:
      {
	if (this->_EllapsedTime >= this->_FrameTime)
	  {
	    if (this->_Status == 3)
	      this->_Old = 0;
	    this->_Status += 1;
	    this->_EllapsedTime = 0;
	  }
      }
    }
}

void	Metroid::GetSprite(int x, int y, unsigned int time, Move move)
{
  if (this->_Etat == 1)
    this->CheckEtat(move,x ,y);
  if (this->_Etat == 1)
    this->FirstState(x, y, time);
  else
    this->CheckSize(time);
}


void	Metroid::setX(int x)
{
  this->_X = x;
}

void	Metroid::setY(int Y)
{
  this->_Y = Y;
}

int	Metroid::getX() const
{
  return (this->_X);
}

int	Metroid::getY() const
{
  return (this->_Y);
}

int	Metroid::getId() const
{
  return (this->_Id);
}

int Metroid::getType() const
{
  return (this->_Type);
}

int	Metroid::getEtat() const
{
  return (this->_Etat);
}

int	Metroid::getStatus() const
{
  return (this->_Status);
}

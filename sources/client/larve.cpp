#include "larve.h"

Larve::Larve()
{
  this->_Status = 1;
  this->_FrameTime = FRAMETIME;
  this->_Etat = 1;
  this->_Size = 3;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 11;
}

Larve::~Larve()
{
}

bool		Larve::SpriteAlive() const
{
  if (this->_Old == 0)
    return (false);
  return (true);
}
void		Larve::ResetData()
{
  this->_Status = 1;
  this->_Etat = 1;
  this->_Size = 3;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 11;  
}
void		Larve::CheckEtat(Move move, int x, int y)
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

void		Larve::FirstState(int x, int y, int time)
{
  this->_X = x;
  this->_Y = y;
  this->_EllapsedTime += time;
  if (this->_EllapsedTime >= this->_FrameTime)
    {
      if (this->_Status == 7)
	this->_Status = -1;
      this->_Status += 1;
      this->_EllapsedTime = 0;
    }
}

void		Larve::CheckSize(int time)
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

void		Larve::GetSprite(int x, int y, unsigned int time, Move move)
{
  if (this->_Etat == 1)
    this->CheckEtat(move,x ,y);
  if (this->_Etat == 1)
    this->FirstState(x, y, time);
  else
    this->CheckSize(time);
}

void	Larve::setX(int x)
{
  this->_X = x;
}

void	Larve::setY(int Y)
{
  this->_Y = Y;
}

int	Larve::getX() const
{
  return (this->_X);
}

int	Larve::getY() const
{
  return (this->_Y);
}

int	Larve::getId() const
{
  return (this->_Id);
}

int Larve::getType()const
{
  return (this->_Type);
}

int	Larve::getEtat() const
{
  return (this->_Etat);
}

int	Larve::getStatus() const
{
  return (this->_Status);
}

void	Larve::setId(int id)
{
  this->_Id = id;
}

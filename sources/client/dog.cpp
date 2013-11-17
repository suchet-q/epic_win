#include "dog.h"

Dog::Dog(int id)
{
  this->_Status = 1;
  this->_Id = id;
  this->_FrameTime = FRAMETIME;
  this->_Old = 1;
  this->_Etat = 1;
  this->_Size = 2;
  this->_EllapsedTime = 0;
  this->_Type = 7;
}

Dog::~Dog()
{  
}

bool		Dog::SpriteAlive() const
{
  if (this->_Old == 0)
    return (false);
  return (true);
}

void		Dog::CheckEtat(Move move, int x, int y)
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

void		Dog::FirstState(int x, int y, int time)
{
  this->_X = x;
  this->_Y = y;
  this->_EllapsedTime += time;
  if (this->_EllapsedTime >= this->_FrameTime)
    {
      if (this->_Status == 5)
	this->_Status = -1;
      this->_Status += 1;
      this->_EllapsedTime = 0;
    }
}

void		Dog::CheckSize(int time)
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

void		Dog::GetSprite(int x, int y, unsigned int time, Move move)
{
  if (this->_Etat == 1)
    this->CheckEtat(move,x ,y);
  if (this->_Etat == 1)
   this->FirstState(x, y, time);
  else
    this->CheckSize(time);
}

void	Dog::setX(int x)
{
  this->_X = x;
}

void	Dog::setY(int Y)
{
  this->_Y = Y;
}

int	Dog::getX() const
{
  return (this->_X);
}

int	Dog::getY() const
{
  return (this->_Y);
}

int	Dog::getId() const
{
  return (this->_Id);
}

int Dog::getType() const
{
  return (this->_Type);
}

int	Dog::getEtat() const
{
  return (this->_Etat);
}

int	Dog::getStatus() const
{
  return (this->_Status);
}

#include "fireball.h"

Fireball::Fireball(int id)
{
  this->_Status = 0;
  this->_Id = id;
  this->_FrameTime = FRAMETIME;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 12;
}

Fireball::~Fireball()
{
}

bool		Fireball::SpriteAlive() const
{
  if (this->_Old == 0)
    return (false);
  return (true);
}

void		Fireball::CheckEtat(Move move, int x, int y)
{
 if (move == DEAD && this->_Etat == 1)
    {
      this->_Etat = 2;
      this->_Status = 4;
      this->_X = x;
      this->_Y = y;
    }
}

void		Fireball::FirstState(int x, int y, int time)
{
  this->_X = x;
  this->_Y = y;
  this->_EllapsedTime += time;
  if (this->_EllapsedTime >= this->_FrameTime)
    {
      if (this->_Status == 3)
	this->_Status = -1;
      this->_Status += 1;
      this->_EllapsedTime = 0;
    }
}


void		Fireball::CheckSize(int time)
{
  time = time;
  // this->_EllapsedTime += time;
  // if (this->_EllapsedTime >= this->_FrameTime)
  //   {
  //     if (this->_Status == 7)
	this->_Old = 0;
      // this->_Status += 1;
      // this->_EllapsedTime = 0;
    // }
}

void		Fireball::GetSprite(int x, int y, unsigned int time, Move move)
{
  if (this->_Etat == 1)
    this->CheckEtat(move,x ,y);
  if (this->_Etat == 1)
    this->FirstState(x, y, time);
  else
    this->CheckSize(time);
}

void	Fireball::setX(int x)
{
  this->_X = x;
}

void	Fireball::setY(int Y)
{
  this->_Y = Y;
}

int	Fireball::getX() const
{
  return (this->_X);
}

int	Fireball::getY() const
{
  return (this->_Y);
}

int	Fireball::getId() const
{
  return (this->_Id);
}

int Fireball::getType() const
{
  return (this->_Type);
}

int	Fireball::getEtat() const
{
  return (this->_Etat);
}

int	Fireball::getStatus() const
{
  return (this->_Status);
}

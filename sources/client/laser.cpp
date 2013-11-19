#include "laser.h"

Laser::Laser()
{
  this->_Status = 0;
  this->_FrameTime = FRAMETIME;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 19;
}

Laser::~Laser()
{
}
void		Laser::ResetData()
{
  this->_Status = 1;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 19;  
}
bool		Laser::SpriteAlive() const
{
  if (this->_Old == 0)
    return (false);
  return (true);
}

void		Laser::CheckEtat(Move move, int x, int y)
{
 if (move == DEAD && this->_Etat == 1)
    {
      this->_Etat = 2;
      this->_Status = 4;
      this->_X = x;
      this->_Y = y;
    }
}

void		Laser::FirstState(int x, int y, int time)
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


void		Laser::CheckSize(int time)
{
  time = time;
  this->_Old = 0;
}

void		Laser::GetSprite(int x, int y, unsigned int time, Move move)
{
  if (this->_Etat == 1)
    this->CheckEtat(move,x ,y);
  if (this->_Etat == 1)
    this->FirstState(x, y, time);
  else
    this->CheckSize(time);
}

void	Laser::setX(int x)
{
  this->_X = x;
}

void	Laser::setY(int Y)
{
  this->_Y = Y;
}

int	Laser::getX() const
{
  return (this->_X);
}

int	Laser::getY() const
{
  return (this->_Y);
}

int	Laser::getId() const
{
  return (this->_Id);
}

int Laser::getType() const
{
  return (this->_Type);
}

int	Laser::getEtat() const
{
  return (this->_Etat);
}

int	Laser::getStatus() const
{
  return (this->_Status);
}

void	Laser::setId(int id)
{
  this->_Id = id;
}

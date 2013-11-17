#include "missil.h"

Missil::Missil(int id)
{
  this->_Status = 0;
  this->_Id = id;
  this->_FrameTime = FRAMETIME;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 13;
}

Missil::~Missil()
{
}

bool		Missil::SpriteAlive() const
{
  if (this->_Old == 0)
    return (false);
  return (true);
}

void		Missil::CheckEtat(Move move, int x, int y)
{
 if (move == DEAD && this->_Etat == 1)
    {
      this->_Etat = 2;
      this->_X = x;
      this->_Y = y;
    }
}

void		Missil::FirstState(int x, int y, int time)
{
  time = time;
  this->_X = x;
  this->_Y = y;
}


void		Missil::CheckSize(int time)
{
  time = time;
  this->_Old = 0;
}

void		Missil::GetSprite(int x, int y, unsigned int time, Move move)
{
  if (this->_Etat == 1)
    this->CheckEtat(move,x ,y);
  if (this->_Etat == 1)
    this->FirstState(x, y, time);
  else
    this->CheckSize(time);
}

void	Missil::setX(int x)
{
  this->_X = x;
}

void	Missil::setY(int Y)
{
  this->_Y = Y;
}

int	Missil::getX() const
{
  return (this->_X);
}

int	Missil::getY() const
{
  return (this->_Y);
}

int	Missil::getId() const
{
  return (this->_Id);
}

int	Missil::getType() const
{
  return (this->_Type);
}

int	Missil::getEtat() const
{
  return (this->_Etat);
}

int	Missil::getStatus() const
{
  return (this->_Status);
}

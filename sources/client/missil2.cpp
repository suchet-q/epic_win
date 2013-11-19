#include "missil2.h"

Missil2::Missil2()
{
  this->_Status = 0;
  this->_FrameTime = FRAMETIME;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 16;
}

Missil2::~Missil2()
{
}

bool		Missil2::SpriteAlive() const
{
  if (this->_Old == 0)
    return (false);
  return (true);
}
void		Missil2::ResetData()
{
  this->_Status = 1;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 16;  
}
void		Missil2::CheckEtat(Move move, int x, int y)
{
 if (move == DEAD && this->_Etat == 1)
    {
      this->_Etat = 2;
      this->_X = x;
      this->_Y = y;
    }
}

void		Missil2::FirstState(int x, int y, int time)
{
  time = time;
  this->_X = x;
  this->_Y = y;
}


void		Missil2::CheckSize(int time)
{
  time = time;
  this->_Old = 0;
  this->_Status = 0;
}

void		Missil2::GetSprite(int x, int y, unsigned int time, Move move)
{
  if (this->_Etat == 1)
    this->CheckEtat(move,x ,y);
  if (this->_Etat == 1)
    this->FirstState(x, y, time);
  else
    this->CheckSize(time);
}

void	Missil2::setX(int x)
{
  this->_X = x;
}

void	Missil2::setY(int Y)
{
  this->_Y = Y;
}

int	Missil2::getX() const
{
  return (this->_X);
}

int	Missil2::getY() const
{
  return (this->_Y);
}

int	Missil2::getId() const
{
  return (this->_Id);
}

int	Missil2::getType() const
{
  return (this->_Type);
}

int	Missil2::getEtat() const
{
  return (this->_Etat);
}

int	Missil2::getStatus() const
{
  return (this->_Status);
}

void	Missil2::setId(int id)
{
  this->_Id = id;
}

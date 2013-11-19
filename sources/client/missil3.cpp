#include "missil3.h"

Missil3::Missil3()
{
  this->_Status = 0;
  this->_FrameTime = FRAMETIME;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 17;
}

Missil3::~Missil3()
{
}

bool		Missil3::SpriteAlive() const
{
  if (this->_Old == 0)
    return (false);
  return (true);
}

void		Missil3::CheckEtat(Move move, int x, int y)
{
 if (move == DEAD && this->_Etat == 1)
    {
      this->_Etat = 2;
      this->_X = x;
      this->_Y = y;
    }
}
void		Missil3::ResetData()
{
  this->_Status = 1;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 17;  
}
void		Missil3::FirstState(int x, int y, int time)
{
  time = time;
  this->_X = x;
  this->_Y = y;
}


void		Missil3::CheckSize(int time)
{
  time = time;
  this->_Old = 0;
  this->_Status = 0;
}

void		Missil3::GetSprite(int x, int y, unsigned int time, Move move)
{
  if (this->_Etat == 1)
    this->CheckEtat(move,x ,y);
  if (this->_Etat == 1)
    this->FirstState(x, y, time);
  else
    this->CheckSize(time);
}

void	Missil3::setX(int x)
{
  this->_X = x;
}

void	Missil3::setY(int Y)
{
  this->_Y = Y;
}

int	Missil3::getX() const
{
  return (this->_X);
}

int	Missil3::getY() const
{
  return (this->_Y);
}

int	Missil3::getId() const
{
  return (this->_Id);
}

int	Missil3::getType() const
{
  return (this->_Type);
}

int	Missil3::getEtat() const
{
  return (this->_Etat);
}

int	Missil3::getStatus() const
{
  return (this->_Status);
}

void	Missil3::setId(int id)
{
  this->_Id = id;
}

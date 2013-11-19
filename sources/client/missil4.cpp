#include "missil4.h"

Missil4::Missil4()
{
  this->_Status = 0;
  this->_FrameTime = FRAMETIME;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 18;
}

Missil4::~Missil4()
{
}

bool		Missil4::SpriteAlive() const
{
  if (this->_Old == 0)
    return (false);
  return (true);
}

void		Missil4::CheckEtat(Move move, int x, int y)
{
 if (move == DEAD && this->_Etat == 1)
    {
      this->_Etat = 2;
      this->_X = x;
      this->_Y = y;
    }
}
void		Missil4::ResetData()
{
  this->_Status = 1;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 18;  
}
void		Missil4::FirstState(int x, int y, int time)
{
  time = time;
  this->_X = x;
  this->_Y = y;
}


void		Missil4::CheckSize(int time)
{
  time = time;
  this->_Old = 0;
  this->_Status = 0;
}

void		Missil4::GetSprite(int x, int y, unsigned int time, Move move)
{
  if (this->_Etat == 1)
    this->CheckEtat(move,x ,y);
  if (this->_Etat == 1)
    this->FirstState(x, y, time);
  else
    this->CheckSize(time);
}

void	Missil4::setX(int x)
{
  this->_X = x;
}

void	Missil4::setY(int Y)
{
  this->_Y = Y;
}

int	Missil4::getX() const
{
  return (this->_X);
}

int	Missil4::getY() const
{
  return (this->_Y);
}

int	Missil4::getId() const
{
  return (this->_Id);
}

int	Missil4::getType() const
{
  return (this->_Type);
}

int	Missil4::getEtat() const
{
  return (this->_Etat);
}

int	Missil4::getStatus() const
{
  return (this->_Status);
}

void	Missil4::setId(int id)
{
  this->_Id = id;
}

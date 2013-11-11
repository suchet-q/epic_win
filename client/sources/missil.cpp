#include "missil.h"

Missil::Missil(int id, sf::Image *img)
{
  sf::Image	*tmp = new sf::Image;

  *tmp = *img;
  this->_MissilAnim = new sf::Sprite[2];
  this->SetSprite(tmp);
  this->CutImage();
  this->_Status = 0;
  this->_Id = id;
  this->_FrameTime = FRAMETIME;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 11;
}

Missil::~Missil()
{
}

bool		Missil::SpriteAlive()
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
      this->_Status = 4;
      this->_X = x;
      this->_Y = y;
    }
}

sf::Sprite	&Missil::FirstState(int x, int y, int time)
{
  this->_EllapsedTime += time;
  if (this->_EllapsedTime >= this->_FrameTime)
    {
      if (this->_Status == 1)
	this->_Status = -1;
      this->_Status += 1;
      this->_EllapsedTime = 0;
    }
  this->_MissilAnim[this->_Status].SetPosition(x, y);
  return (this->_MissilAnim[this->_Status]);
}


sf::Sprite	&Missil::CheckSize(int x, int y, int time)
{
  this->_EllapsedTime += time;
  if (this->_EllapsedTime >= this->_FrameTime)
    {
      if (this->_Status == 7)
	this->_Old = 0;
      this->_Status += 1;
      this->_MissilAnim[this->_Status].SetPosition(this->_X, this->_Y);
      this->_EllapsedTime = 0;
      return (this->_MissilAnim[this->_Status]);
    }
  else
    {
      this->_MissilAnim[this->_Status].SetPosition(this->_X, this->_Y);
      return (this->_MissilAnim[this->_Status]);
    }
}

sf::Sprite	&Missil::GetSprite(int x, int y, unsigned int time, Move move)
{
  if (this->_Etat == 1)
    this->CheckEtat(move,x ,y);
  if (this->_Etat == 1)
    return (this->FirstState(x, y, time));
  else
    return (this->CheckSize(x, y, time));
}

void	Missil::SetSprite(sf::Image *img)
{
  int	x = 0;

  while (x < 2)
    {
      this->_MissilAnim[x].SetImage(*img);
      x++;
    }
}

void	Missil::CutImage()
{
  int	Width = 532;
  int	Height = 372;
  int	x = 0;
  int	j = 8;
  while (x < 2)
    {
      this->_MissilAnim[x].SetSubRect(sf::IntRect((Width/20 - 2) * j, Height/4 + 5, (Width/20 - 1)*(j+1),Height/3 - 5));
      x++;
      j++;
    }
}

void	Missil::setX(int x)
{
  this->_X = x;
}

void	Missil::setY(int Y)
{
  this->_Y = Y;
}

int	Missil::getX()
{
  return (this->_X);
}

int	Missil::getY()
{
  return (this->_Y);
}

int	Missil::getId()
{
  return (this->_Id);
}

unsigned char Missil::getType()
{
  return (this->_Type);
}

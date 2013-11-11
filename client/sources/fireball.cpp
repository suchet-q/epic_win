#include "fireball.h"

Fireball::Fireball(int id, sf::Image *img)
{
  sf::Image	*tmp = new sf::Image;

  *tmp = *img;
  this->_FireballAnim = new sf::Sprite[9];
  this->SetSprite(tmp);
  this->CutImage();
  this->_Status = 0;
  this->_Id = id;
  this->_FrameTime = FRAMETIME;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 10;
}

Fireball::~Fireball()
{
}

bool		Fireball::SpriteAlive()
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

sf::Sprite	&Fireball::FirstState(int x, int y, int time)
{
  this->_EllapsedTime += time;
  if (this->_EllapsedTime >= this->_FrameTime)
    {
      if (this->_Status == 3)
	this->_Status = -1;
      this->_Status += 1;
      this->_EllapsedTime = 0;
    }
  this->_FireballAnim[this->_Status].SetPosition(x, y);
  return (this->_FireballAnim[this->_Status]);
}


sf::Sprite	&Fireball::CheckSize(int x, int y, int time)
{
  this->_EllapsedTime += time;
  if (this->_EllapsedTime >= this->_FrameTime)
    {
      if (this->_Status == 7)
	this->_Old = 0;
      this->_Status += 1;
      this->_FireballAnim[this->_Status].SetPosition(this->_X, this->_Y);
      this->_EllapsedTime = 0;
      return (this->_FireballAnim[this->_Status]);
    }
  else
    {
      this->_FireballAnim[this->_Status].SetPosition(this->_X, this->_Y);
      return (this->_FireballAnim[this->_Status]);
    }
}

sf::Sprite	&Fireball::GetSprite(int x, int y, unsigned int time, Move move)
{
  if (this->_Etat == 1)
    this->CheckEtat(move,x ,y);
  if (this->_Etat == 1)
    return (this->FirstState(x, y, time));
  else
    return (this->CheckSize(x, y, time));
}

void	Fireball::SetSprite(sf::Image *img)
{
  int	x = 0;

  while (x < 9)
    {
      this->_FireballAnim[x].SetImage(*img);
      x++;
    }
}

void	Fireball::CutImage()
{
  int	Width = 400;
  int	Height = 85;
  int	x = 0;
  int	j = 8;

  while (j < 12)
    {
      this->_FireballAnim[x].SetSubRect(sf::IntRect((Width/24 + 1) * j, 0, (Width/24 + 1)*(j+1),Height/4));
      x++;
      j++;
    }
  j = 7;
  while (j < 12)
    {
      this->_FireballAnim[x].SetSubRect(sf::IntRect((Width/24) * j, Height/4, (Width/24)*(j+1),Height/2 - 10));
      x++;
      j++;
    }

}

void	Fireball::setX(int x)
{
  this->_X = x;
}

void	Fireball::setY(int Y)
{
  this->_Y = Y;
}

int	Fireball::getX()
{
  return (this->_X);
}

int	Fireball::getY()
{
  return (this->_Y);
}

int	Fireball::getId()
{
  return (this->_Id);
}

unsigned char Fireball::getType()
{
  return (this->_Type);
}

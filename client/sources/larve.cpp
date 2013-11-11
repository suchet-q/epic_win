#include "larve.h"

Larve::Larve(int id, sf::Image *img, sf::Image *explosion)
{
  sf::Image	*tmp = new sf::Image;

  *tmp = *img;
  this->_LarveAnim = new sf::Sprite[8];
  this->_Explosion = new Explosion(explosion);
  this->SetSprite(tmp);
  this->CutImage();
  this->_Status = 1;
  this->_Id = id;
  this->_FrameTime = FRAMETIME;
  this->_Etat = 1;
  this->_Size = 3;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 8;
}

Larve::~Larve()
{
}

bool		Larve::SpriteAlive()
{
  if (this->_Old == 0)
    return (false);
  return (true);
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

sf::Sprite	&Larve::FirstState(int x, int y, int time)
{
  this->_EllapsedTime += time;
  if (this->_EllapsedTime >= this->_FrameTime)
    {
      if (this->_Status == 7)
	this->_Status = -1;
      this->_Status += 1;
      this->_EllapsedTime = 0;
    }
  this->_LarveAnim[this->_Status].SetPosition(x, y);
  return (this->_LarveAnim[this->_Status]);
}


sf::Sprite	&Larve::CheckSize(int x, int y, int time)
{
  this->_EllapsedTime += time;
  switch (this->_Size)
    {
    case 1:
      {
	if (this->_EllapsedTime >= this->_FrameTime)
	  {
	    if (this->_Status == 12)
	      this->_Old = 0;
	    this->_Status += 1;
	    this->_Explosion->_ExplosionAnim[this->_Status].SetPosition(this->_X, this->_Y);
	    this->_EllapsedTime = 0;
	    return (this->_Explosion->_ExplosionAnim[this->_Status]);
	  }
	else
	  {
	    this->_Explosion->_ExplosionAnim[this->_Status].SetPosition(this->_X, this->_Y);
	    return (this->_Explosion->_ExplosionAnim[this->_Status]);
	  }
      }
    case 2:
      {
	if ( this->_EllapsedTime >= this->_FrameTime)
	  {
	    if (this->_Status == 7)
	      this->_Old = 0;
	    this->_Status += 1;
	    this->_Explosion->_ExplosionAnim[this->_Status].SetPosition(this->_X, this->_Y);
	    this->_EllapsedTime = 0;
	    return (this->_Explosion->_ExplosionAnim[this->_Status]);
	  }
	else
	  {
	    this->_Explosion->_ExplosionAnim[this->_Status].SetPosition(this->_X, this->_Y);
	    return (this->_Explosion->_ExplosionAnim[this->_Status]);
	  }
      }
    case 3:
      {
	if (this->_EllapsedTime >= this->_FrameTime)
	  {
	    if (this->_Status == 4)
	      this->_Old = 0;
	    this->_Status += 1;
	    this->_Explosion->_ExplosionAnim[this->_Status].SetPosition(this->_X, this->_Y);
	    this->_EllapsedTime = 0;
	    return (this->_Explosion->_ExplosionAnim[this->_Status]);
	  }
	else
	  {
	    this->_Explosion->_ExplosionAnim[this->_Status].SetPosition(this->_X, this->_Y);
	    return (this->_Explosion->_ExplosionAnim[this->_Status]);
	  }      
      }
    }
}

sf::Sprite	&Larve::GetSprite(int x, int y, unsigned int time, Move move)
{
  if (this->_Etat == 1)
    this->CheckEtat(move,x ,y);
  if (this->_Etat == 1)
    return (this->FirstState(x, y, time));
  else
    return (this->CheckSize(x, y, time));
}

void	Larve::SetSprite(sf::Image *img)
{
  int	x = 0;

  while (x < 8)
    {
      this->_LarveAnim[x].SetImage(*img);
      x++;
    }
}

void	Larve::CutImage()
{
  int	Width = 522;
  int	Height = 132;
  int	x = 0;

  while (x < 8)
    {
      this->_LarveAnim[x].SetSubRect(sf::IntRect(Width/8 * x, 0, Width/8*(x+1),132));
      x++;
    }
}

void	Larve::setX(int x)
{
  this->_X = x;
}

void	Larve::setY(int Y)
{
  this->_Y = Y;
}

int	Larve::getX()
{
  return (this->_X);
}

int	Larve::getY()
{
  return (this->_Y);
}

int	Larve::getId()
{
  return (this->_Id);
}

unsigned char Larve::getType()
{
  return (this->_Type);
}

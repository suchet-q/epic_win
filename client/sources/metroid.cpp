#include "metroid.h"

Metroid::Metroid(int id, sf::Image *img, sf::Image *explosion)
{
  this->_MetroidAnim = new sf::Sprite[5];
  this->_Explosion = new Explosion(explosion);
  this->SetSprite(img);
  this->CutImage();
  this->_Status = 1;
  this->_Id = id;
  this->_FrameTime = FRAMETIME;
  this->_Old = 1;
  this->_Etat = 1;
  this->_Size = 3;
  this->_EllapsedTime = 0;
  this->_Type = 7;
}

Metroid::~Metroid()
{  
}

bool		Metroid::SpriteAlive()
{
  if (this->_Old == 0)
    return (false);
  return (true);
}

void		Metroid::CheckEtat(Move move, int x, int y)
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

sf::Sprite	&Metroid::FirstState(int x, int y, int time)
{
  
  this->_EllapsedTime += time;
  if (this->_EllapsedTime >= this->_FrameTime)
    {
      if (this->_Status == 4)
	this->_Status = -1;
      this->_Status += 1;
      this->_EllapsedTime = 0;
    }
  this->_MetroidAnim[this->_Status].SetPosition(x, y);
  return (this->_MetroidAnim[this->_Status]);
}


sf::Sprite	&Metroid::CheckSize(int x, int y, int time)
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

sf::Sprite	&Metroid::GetSprite(int x, int y, unsigned int time, Move move)
{
  if (this->_Etat == 1)
    this->CheckEtat(move,x ,y);
  if (this->_Etat == 1)
    return (this->FirstState(x, y, time));
  else
    return (this->CheckSize(x, y, time));
}

void	Metroid::SetSprite(sf::Image *img)
{
  int	x = 0;

  while (x < 5)
    {
      this->_MetroidAnim[x].SetImage(*img);
      x++;
    }
}

void	Metroid::CutImage()
{
  int	Width = 326;
  int	Height = 66;
  int	x = 0;

  while (x < 5)
    {
      this->_MetroidAnim[x].SetSubRect(sf::IntRect(Width/5 * x, 0, Width/5*(x+1),66));
      x++;
    }
}

void	Metroid::setX(int x)
{
  this->_X = x;
}

void	Metroid::setY(int Y)
{
  this->_Y = Y;
}

int	Metroid::getX()
{
  return (this->_X);
}

int	Metroid::getY()
{
  return (this->_Y);
}

int	Metroid::getId()
{
  return (this->_Id);
}

unsigned char Metroid::getType()
{
  return (this->_Type);
}

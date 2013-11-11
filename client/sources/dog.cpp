#include "dog.h"

Dog::Dog(int id, sf::Image *img, sf::Image *explosion)
{
  this->_DogAnim = new sf::Sprite[6];
  this->_Explosion = new Explosion(explosion);
  this->SetSprite(img);
  this->CutImage();
  this->_Status = 1;
  this->_Id = id;
  this->_FrameTime = FRAMETIME;
  this->_Old = 1;
  this->_Etat = 1;
  this->_Size = 2;
  this->_EllapsedTime = 0;
  this->_Type = 4;
}

Dog::~Dog()
{  
}

bool		Dog::SpriteAlive()
{
  if (this->_Old == 0)
    return (false);
  return (true);
}

void		Dog::CheckEtat(Move move, int x, int y)
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

sf::Sprite	&Dog::FirstState(int x, int y, int time)
{
  this->_EllapsedTime += time;
  if (this->_EllapsedTime >= this->_FrameTime)
    {
      if (this->_Status == 5)
	this->_Status = -1;
      this->_Status += 1;
      this->_EllapsedTime = 0;
    }
  this->_DogAnim[this->_Status].SetPosition(x, y);
  return (this->_DogAnim[this->_Status]);
}

sf::Sprite	&Dog::CheckSize(int x, int y, int time)
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

sf::Sprite	&Dog::GetSprite(int x, int y, unsigned int time, Move move)
{
  if (this->_Etat == 1)
    this->CheckEtat(move,x ,y);
  if (this->_Etat == 1)
    return (this->FirstState(x, y, time));
  else
    return (this->CheckSize(x, y, time));
}

void	Dog::SetSprite(sf::Image *img)
{
  int	x = 0;

  while (x < 6)
    {
      this->_DogAnim[x].SetImage(*img);
      x++;
    }
}

void	Dog::CutImage()
{
  int	Width = 398;
  int	Height = 100;
  int	x = 0;

  while (x < 6)
    {
      this->_DogAnim[x].SetSubRect(sf::IntRect(Width/12 * x, 0, Width/12*(x+1),Height / 3));
      x++;
    }
}

void	Dog::setX(int x)
{
  this->_X = x;
}

void	Dog::setY(int Y)
{
  this->_Y = Y;
}

int	Dog::getX()
{
  return (this->_X);
}

int	Dog::getY()
{
  return (this->_Y);
}

int	Dog::getId()
{
  return (this->_Id);
}

unsigned char Dog::getType()
{
  return (this->_Type);
}

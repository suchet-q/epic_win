#include "drone.h"

Drone::Drone(int id, sf::Image *img, sf::Image *explosion)
{
  sf::Image	*tmp = new sf::Image;

  *tmp = *img;
  this->_DroneAnim = new sf::Sprite[8];
  this->_Explosion = new Explosion(explosion);
  this->SetSprite(tmp);
  this->CutImage();
  this->_Status = 1;
  this->_Id = id;
  this->_FrameTime = FRAMETIME;
  this->_Etat = 1;
  this->_Size = 1;
  this->_Old = 1;
  this->_EllapsedTime = 0;
  this->_Type = 2;
}

Drone::~Drone()
{
}

bool		Drone::SpriteAlive()
{
  if (this->_Old == 0)
    return (false);
  return (true);
}

void		Drone::CheckEtat(Move move, int x, int y)
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

sf::Sprite	&Drone::FirstState(int x, int y, int time)
{
  this->_EllapsedTime += time;
  if (this->_EllapsedTime >= this->_FrameTime)
    {
      if (this->_Status == 7)
	this->_Status = -1;
      this->_Status += 1;
      this->_EllapsedTime = 0;
    }
  this->_DroneAnim[this->_Status].SetPosition(x, y);
  return (this->_DroneAnim[this->_Status]);
}


sf::Sprite	&Drone::CheckSize(int x, int y, int time)
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
	if (this->_EllapsedTime >= this->_FrameTime)
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

sf::Sprite	&Drone::GetSprite(int x, int y, unsigned int time, Move move)
{
  if (this->_Etat == 1)
    this->CheckEtat(move,x ,y);
  if (this->_Etat == 1)
    return (this->FirstState(x, y, time));
  else
    return (this->CheckSize(x, y, time));
}

void	Drone::SetSprite(sf::Image *img)
{
  int	x = 0;

  while (x < 8)
    {
      this->_DroneAnim[x].SetImage(*img);
      x++;
    }
}

void	Drone::CutImage()
{
  int	Width = 533;
  int	Height = 36;
  int	x = 0;

  while (x < 8)
    {
      this->_DroneAnim[x].SetSubRect(sf::IntRect(Width/16 * x, 0, Width/16*(x+1),36));
      x++;
    }
}

void	Drone::setX(int x)
{
  this->_X = x;
}

void	Drone::setY(int Y)
{
  this->_Y = Y;
}

int	Drone::getX()
{
  return (this->_X);
}

int	Drone::getY()
{
  return (this->_Y);
}

int	Drone::getId()
{
  return (this->_Id);
}

unsigned char Drone::getType()
{
  return (this->_Type);
}

int	Drone::getEtat()
{
  return (this->_Etat);
}

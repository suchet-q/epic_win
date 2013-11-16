#include "explosion.h"

Explosion::Explosion(sf::Image *img)
{
  sf::Image *tmp = new sf::Image;

  *tmp = *img;
  this->_ExplosionAnim = new sf::Sprite[14];
  this->SetSprite(tmp);
  this->CutImage();
  this->_Status = 0;
  this->_FrameTime = FRAMETIME;
}

Explosion::~Explosion()
{  
}

sf::Sprite	&Explosion::GetSprite(int x, int y, unsigned int time, Move move, int Status)
{
  return (this->_ExplosionAnim[Status]);
}

void	Explosion::SetSprite(sf::Image *img)
{
  int	x = 0;

  while (x < 14)
    {
      this->_ExplosionAnim[x].SetImage(*img);
      x++;
    }
}

void	Explosion::CutImage()
{
  int	Width = 652;
  int	Height = 164;
  int	x = 0;
  int	j = 2;
  
  while (x < 5)
    {
      this->_ExplosionAnim[x].SetSubRect(sf::IntRect(Width/10 * x, Height/2 + 12, Width/10*(x+1),164));
      x++;
    }
  while (j < 5)
    {
      this->_ExplosionAnim[x].SetSubRect(sf::IntRect(Width/10 * j, Height/6 + 12, Width/10*(j+1),Height/2 + 10));
      x++;
      j++;
    }
  j = 4;
  while (j < 12)
    {
      this->_ExplosionAnim[x].SetSubRect(sf::IntRect(Width/20 * j, 0, Width/20*(j+1),Height/6 + 10));
      j++;
      x++;
    }  
}

void	Explosion::setX(int x)
{
  this->_X = x;
}
void	Explosion::setY(int Y)
{
  this->_Y = Y;
}

int	Explosion::getX()
{
  return (this->_X);
}

int	Explosion::getY()
{
  return (this->_Y);
}

int	Explosion::getId()
{
  return (this->_Id);
}

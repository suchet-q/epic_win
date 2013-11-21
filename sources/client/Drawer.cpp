#include "Drawer.h"

Drawer::Drawer(sf::RenderWindow *window, sf::Mutex *mutex)
{
  this->_Mutex = mutex;
  this->Window = window;
  this->_DroneImg = new sf::Texture;
  this->_BallsImg = new sf::Texture;
  this->_AlienImg = new sf::Texture;
  this->_DogImg = new sf::Texture;
  this->_JumperImg = new sf::Texture;
  this->_XwingImg = new sf::Texture;
  this->_MetroidImg = new sf::Texture;
  this->_ExplosionImg = new sf::Texture;
  this->_LarveImg = new sf::Texture;
  this->_FireballImg = new sf::Texture;
  this->_MissilImg = new sf::Texture;
  this->_ShipImg = new sf::Texture;
  this->_LaserImg = new sf::Texture;
  this->_Decor1topImg = new sf::Texture;
  this->_Decor1downImg = new sf::Texture;
  this->_Decor2topImg = new sf::Texture;
  this->_Decor2downImg = new sf::Texture;

  this->_XwingAnim = new sf::Sprite[8];
  this->_MissilAnim = new sf::Sprite[4];
  this->_MetroidAnim = new sf::Sprite[5];
  this->_LarveAnim = new sf::Sprite[8];
  this->_JumperAnim = new sf::Sprite[3];
  this->_FireballAnim = new sf::Sprite[9];
  this->_ExplosionAnim = new sf::Sprite[14];
  this->_DroneAnim = new sf::Sprite[8];
  this->_DogAnim = new sf::Sprite[6];
  this->_BallsAnim = new sf::Sprite[12];
  this->_AlienAnim = new sf::Sprite[6];
  this->_Ship1Anim = new sf::Sprite[5];
  this->_Ship2Anim = new sf::Sprite[5];
  this->_Ship3Anim = new sf::Sprite[5];
  this->_Ship4Anim = new sf::Sprite[5];
  this->_LaserAnim = new sf::Sprite[8];
  this->_DecorAnim = new sf::Sprite[4];

  fct = new pfSprite[23];
  fct[0] = &Drawer::drowShip1;
  fct[1] = &Drawer::drowShip2;
  fct[2] = &Drawer::drowShip3;
  fct[3] = &Drawer::drowShip4;
  fct[4] = &Drawer::drowDrone;
  fct[5] = &Drawer::drowAlien;
  fct[6] = &Drawer::drowDog;
  fct[7] = &Drawer::drowJumper;
  fct[8] = &Drawer::drowXwing;
  fct[9] = &Drawer::drowMetroid;
  fct[10] = &Drawer::drowLarve;
  fct[11] = &Drawer::drowFireBall;
  fct[12] = &Drawer::drowMissil;
  fct[13] = &Drawer::drowBalls;
  fct[14] = &Drawer::drowExplosion;
  fct[15] = &Drawer::drowMissil2;
  fct[16] = &Drawer::drowMissil3;
  fct[17] = &Drawer::drowMissil4;
  fct[18] = &Drawer::drowLaser;
  fct[19] = &Drawer::drowDecor1Top;
  fct[20] = &Drawer::drowDecor1Down;
  fct[21] = &Drawer::drowDecor2Top;
  fct[22] = &Drawer::drowDecor2Down;
}

Drawer::~Drawer()
{
  delete this->_DroneImg;
  delete this->_BallsImg;
  delete this->_AlienImg;
  delete this->_DogImg;
  delete this->_JumperImg;
  delete this->_XwingImg;
  delete this->_MetroidImg;
  delete this->_ExplosionImg;
  delete this->_LarveImg;
  delete this->_FireballImg;
  delete this->_MissilImg;
  delete this->_ShipImg;
  delete this->_LaserImg;
  delete this->_Decor1topImg;
  delete this->_Decor1downImg;
  delete this->_Decor2topImg;
  delete this->_Decor2downImg;

  delete this->_XwingAnim;
  delete this->_MissilAnim;
  delete this->_MetroidAnim;
  delete this->_LarveAnim;
  delete this->_JumperAnim;
  delete this->_FireballAnim;
  delete this->_ExplosionAnim;
  delete this->_DroneAnim;
  delete this->_DogAnim;
  delete this->_BallsAnim;
  delete this->_AlienAnim;
  delete this->_Ship1Anim;
  delete this->_Ship2Anim;
  delete this->_Ship3Anim;
  delete this->_Ship4Anim;
  delete this->_LaserAnim;
  delete this->_DecorAnim;
}

bool	Drawer::InitSprite()
{
  if (this->SetImg() == false)
      return (false);
  this->SetSprite();
  this->CutImg();
  return true;
}

bool	Drawer::SetImg()
{
  if (!this->_DroneImg->loadFromFile("./sprites/r-typesheet5.png"))
    return (false);
  if (!this->_BallsImg->loadFromFile("./sprites/r-typesheet3.png"))
    return (false);
  if (!this->_AlienImg->loadFromFile("./sprites/r-typesheet11.png"))
    return (false);
  if (!this->_DogImg->loadFromFile("./sprites/r-typesheet10.png"))
    return (false);
  if (!this->_JumperImg->loadFromFile("./sprites/r-typesheet9.png"))
    return (false);
  if (!this->_XwingImg->loadFromFile("./sprites/r-typesheet23.png"))
    return (false);
  if (!this->_MetroidImg->loadFromFile("./sprites/r-typesheet24.png"))
    return (false);
  if (!this->_ExplosionImg->loadFromFile("./sprites/r-typesheet44.png"))
    return (false);
  if (!this->_LarveImg->loadFromFile("./sprites/r-typesheet17.png"))
    return (false);
  if (!this->_FireballImg->loadFromFile("./sprites/r-typesheet43.png"))
    return (false);
  if (!this->_MissilImg->loadFromFile("./sprites/r-typesheet1.png"))
    return (false);
  if (!this->_ShipImg->loadFromFile("./sprites/r-typesheet42.png"))
    return (false);
	//this->_ShipImg->CreateMaskFromColor(sf::Color(0,0,0));
  if (!this->_LaserImg->loadFromFile("./sprites/r-typesheet2.png"))
    return (false);
  if (!this->_Decor1topImg->loadFromFile("./sprites/monster_revert.png"))
    return (false);
  if (!this->_Decor1downImg->loadFromFile("./sprites/monster.png"))
    return (false);
  if (!this->_Decor2topImg->loadFromFile("./sprites/bidule_revert.png"))
    return (false);
  if (!this->_Decor2downImg->loadFromFile("./sprites/bidule.png"))
    return (false);
  return true;
}

void	Drawer::SetSprite()
{
  int	x;

  for (x = 0; x < 3; ++x)
    this->_JumperAnim[x].setTexture(*this->_JumperImg);
  for (x = 0; x < 5; ++x)
    {
      this->_MetroidAnim[x].setTexture(*this->_MetroidImg);
      this->_Ship1Anim[x].setTexture(*this->_ShipImg);
      this->_Ship2Anim[x].setTexture(*this->_ShipImg);
      this->_Ship3Anim[x].setTexture(*this->_ShipImg);
      this->_Ship4Anim[x].setTexture(*this->_ShipImg);
    }
  for (x  = 0; x < 6; ++x)
    {
      this->_DogAnim[x].setTexture(*this->_DogImg);
      this->_AlienAnim[x].setTexture(*this->_AlienImg);
    }
  for (x = 0; x < 8; ++x)
    {
      this->_XwingAnim[x].setTexture(*this->_XwingImg);
      this->_LarveAnim[x].setTexture(*this->_LarveImg);
      this->_DroneAnim[x].setTexture(*this->_DroneImg);
    }
  for (x = 0; x < 9; ++x)
    this->_FireballAnim[x].setTexture(*this->_FireballImg);
  for (x = 0; x < 12; ++x)
    this->_BallsAnim[x].setTexture(*this->_BallsImg);
  for (x = 0; x < 14; ++x)
    this->_ExplosionAnim[x].setTexture(*this->_ExplosionImg);
  for (x = 0; x < 4; ++x)
    this->_MissilAnim[x].setTexture(*this->_MissilImg);
  for (x = 0; x < 8; ++x)
    this->_LaserAnim[x].setTexture(*this->_LaserImg);
  this->_DecorAnim[0].setTexture(*this->_Decor1topImg);
  this->_DecorAnim[1].setTexture(*this->_Decor1downImg);
  this->_DecorAnim[2].setTexture(*this->_Decor2topImg);
  this->_DecorAnim[3].setTexture(*this->_Decor2downImg);

}

void	Drawer::CutImg()
{
  int x;

  for (x = 0; x < 8; ++x)
    this->_XwingAnim[x].setTextureRect(sf::IntRect(265/8 * x, 0, 265/8*(x+1),67/2));

  int j = 8;
  this->_MissilAnim[0].setTextureRect(sf::IntRect(230, 372/3 - 9, 532/2, 372/3 + 10));
  this->_MissilAnim[1].setTextureRect(sf::IntRect(230, 372/3 + 10, 532/2, 372/3 + 30));
  this->_MissilAnim[2].setTextureRect(sf::IntRect(199, 372/3 + 30, 532/2, 372/3 + 44));
  this->_MissilAnim[3].setTextureRect(sf::IntRect(185, 372/3 + 44, 532/2, 372/2));

  for (x = 0; x < 5; ++x)
    this->_MetroidAnim[x].setTextureRect(sf::IntRect(326/5 * x, 0, 326/5*(x+1),66));

  for (x = 0; x < 8; ++x)
    this->_LarveAnim[x].setTextureRect(sf::IntRect(522/8 * x, 0, 522/8*(x+1),132));

  for (x = 0; x < 3; ++x)
    this->_JumperAnim[x].setTextureRect(sf::IntRect(332/6 * x, 0, 332/6*(x+1),60));

  j = 8;
  x = 0;
  while (j < 12)
    {
      this->_FireballAnim[x].setTextureRect(sf::IntRect((400/24 + 1) * j, 0, (400/24 + 1)*(j+1),85/4));
      x++;
      j++;
    }
  j = 7;
  while (j < 12)
    {
      this->_FireballAnim[x].setTextureRect(sf::IntRect((400/24) * j, 85/4, (400/24)*(j+1),85/2 - 10));
      x++;
      j++;
    }
  x = 0;
  j = 2;
  while (x < 5)
    {
      this->_ExplosionAnim[x].setTextureRect(sf::IntRect(652/10 * x, 164/2 + 12, 652/10*(x+1),164));
      x++;
    }
  while (j < 5)
    {
      this->_ExplosionAnim[x].setTextureRect(sf::IntRect(652/10 * j, 164/6 + 12, 652/10*(j+1),164/2 + 10));
      x++;
      j++;
    }

  j = 4;
  while (j < 10)
    {
      this->_ExplosionAnim[x].setTextureRect(sf::IntRect(652/20 * j, 0, 652/20*(j+1),164/6 + 10));
      j++;
      x++;
    }  
  for (x = 0; x < 8; ++x)
    this->_DroneAnim[x].setTextureRect(sf::IntRect(533/16 * x, 0, 533/16*(x+1),36));

  for (x = 0; x < 6; ++x)
    this->_DogAnim[x].setTextureRect(sf::IntRect(398/12 * x, 0, 398/12*(x+1),100 / 3));

  for (x = 0; x < 12; ++x)
    this->_BallsAnim[x].setTextureRect(sf::IntRect(208/12 * x, 0, 208/12*(x+1),18));

  for (x = 0; x < 6; ++x)
    this->_AlienAnim[x].setTextureRect(sf::IntRect(200/6 * x, 0, 200/6*(x+1),34));

  for (x = 0; x < 5; ++x)
    {
	this->_Ship1Anim[x].setScale(2.0f, 2.0f);
      this->_Ship1Anim[x].setTextureRect(sf::IntRect((166 / 5) * x,0,(166/5) * (x+1),86 / 5));
	  this->_Ship2Anim[x].setScale(2.0f, 2.0f);
      this->_Ship2Anim[x].setTextureRect(sf::IntRect((166 / 5) * x, 86 / 5 ,(166/5) * (x+1), (86/5) * 2));
	  this->_Ship3Anim[x].setScale(2.0f, 2.0f);
      this->_Ship3Anim[x].setTextureRect(sf::IntRect((166 / 5) * x, (86 / 5) * 2 ,(166/5) * (x+1), (86/5) * 3));
	  this->_Ship4Anim[x].setScale(2.0f, 2.0f);
      this->_Ship4Anim[x].setTextureRect(sf::IntRect((166 / 5) * x, (86 / 5) * 3 ,(166/5) * (x+1), (86/5) * 4));
    }
  this->_LaserAnim[0].setTextureRect(sf::IntRect(38,471,100,502));
  this->_LaserAnim[1].setTextureRect(sf::IntRect(104,471,168,502));
  this->_LaserAnim[2].setTextureRect(sf::IntRect(170,471,230,502));
  this->_LaserAnim[3].setTextureRect(sf::IntRect(235,471,300,502));
  this->_LaserAnim[4].setTextureRect(sf::IntRect(38,505,100,536));
  this->_LaserAnim[5].setTextureRect(sf::IntRect(105,505,167,536));
  this->_LaserAnim[6].setTextureRect(sf::IntRect(170,505,232,536));
  this->_LaserAnim[7].setTextureRect(sf::IntRect(235,505,297,536));
}

void	Drawer::drowLaser(int x, int y, int status)
{
  this->_LaserAnim[status].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_LaserAnim[status]);
  ////this->_Mutex->Unlock();
}

void	Drawer::drowShip1(int x, int y, int status)
{
  this->_Ship1Anim[status].setPosition(x, y);
  ////this->_Mutex->Lock();
  this->Window->draw(this->_Ship1Anim[status]);
  ////this->_Mutex->Unlock();
}

void	Drawer::drowShip2(int x, int y, int status)
{
  this->_Ship2Anim[status].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_Ship2Anim[status]);
  //this->_Mutex->Unlock();
}

void	Drawer::drowShip3(int x, int y, int status)
{
  this->_Ship3Anim[status].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_Ship3Anim[status]);
  //this->_Mutex->Unlock();
}

void	Drawer::drowShip4(int x, int y, int status)
{
  this->_Ship4Anim[status].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_Ship4Anim[status]);
  //this->_Mutex->Unlock();
}

void	Drawer::drowDrone(int x, int y, int status)
{
  this->_DroneAnim[status].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_DroneAnim[status]);
  //this->_Mutex->Unlock();
}

void	Drawer::drowExplosion(int x, int y, int status)
{
  this->_ExplosionAnim[status].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_ExplosionAnim[status]);
  //this->_Mutex->Unlock();
}

void	Drawer::drowAlien(int x, int y, int status)
{
  this->_AlienAnim[status].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_AlienAnim[status]);
  //this->_Mutex->Unlock();
}

void	Drawer::drowBalls(int x, int y, int status)
{
  this->_BallsAnim[status].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_BallsAnim[status]);
  //this->_Mutex->Unlock();
}

void	Drawer::drowDog(int x, int y, int status)
{
  this->_DogAnim[status].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_DogAnim[status]);
  //this->_Mutex->Unlock();
}

void	Drawer::drowJumper(int x, int y, int status)
{
  this->_JumperAnim[status].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_JumperAnim[status]);
  //this->_Mutex->Unlock();
}

void	Drawer::drowXwing(int x, int y, int status)
{
  this->_XwingAnim[status].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_XwingAnim[status]);
  //this->_Mutex->Unlock();
}

void	Drawer::drowMetroid(int x, int y, int status)
{
  this->_MetroidAnim[status].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_MetroidAnim[status]);
  //this->_Mutex->Unlock();
}

void	Drawer::drowLarve(int x, int y, int status)
{
  this->_LarveAnim[status].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_LarveAnim[status]);
  //this->_Mutex->Unlock();
}

void	Drawer::drowFireBall(int x, int y, int status)
{
  this->_FireballAnim[status].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_FireballAnim[status]);
  //this->_Mutex->Unlock();
}

void	Drawer::drowDecor1Top(int x, int y, int status)
{
  status = status;
  this->_DecorAnim[0].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_DecorAnim[0]);
  //this->_Mutex->Unlock();
}

void	Drawer::drowDecor1Down(int x, int y, int status)
{
  status = status;
  this->_DecorAnim[1].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_DecorAnim[1]);
  //this->_Mutex->Unlock();
}

void	Drawer::drowDecor2Top(int x, int y, int status)
{
  status = status;
  this->_DecorAnim[2].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_DecorAnim[2]);
  //this->_Mutex->Unlock();
}

void	Drawer::drowDecor2Down(int x, int y, int status)
{
  status = status;
  this->_DecorAnim[3].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_DecorAnim[3]);
  //this->_Mutex->Unlock();
}

void	Drawer::drowMissil(int x, int y, int status)
{
  status = status;
  this->_MissilAnim[0].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_MissilAnim[0]);
  //this->_Mutex->Unlock();
}

void	Drawer::drowMissil2(int x, int y, int status)
{
  status = status;
  this->_MissilAnim[1].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_MissilAnim[1]);
  //this->_Mutex->Unlock();
}

void	Drawer::drowMissil3(int x, int y, int status)
{
  status = status;
  this->_MissilAnim[2].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_MissilAnim[2]);
  //this->_Mutex->Unlock();
}
void	Drawer::drowMissil4(int x, int y, int status)
{
  status = status;
  this->_MissilAnim[3].setPosition(x, y);
  //this->_Mutex->Lock();
  this->Window->draw(this->_MissilAnim[3]);
  //this->_Mutex->Unlock();
}

void	Drawer::drowSprite(int type, int x, int y, int status)
{
  (this->*fct[type])(x, y, status);
}

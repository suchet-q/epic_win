//
// ship.cpp for ship in /home/heuzey_m//TEK3/R-TYPE
// 
// Made by mathieu heuzey
// Login   <heuzey_m@epitech.net>
// 
// Started on  Sat Oct 26 23:30:25 2013 mathieu heuzey
// Last update Sun Nov 17 01:04:36 2013 mathieu heuzey
//

#include "ship.h"

Ship::Ship(int x, int y, int team, int id)
{
  this->_Status = 2;
  this->_Team = team;
  this->_EllapsedTime = FRAMETIME;
  this->_FrameTime = FRAMETIME;
  this->_Type = 1;
  this->_Id = id;
  this->_Old = 1;
  this->_X = x;
  this->_Y = y;
  this->_Inputs = NOTHING;
  this->_Etat = 1;
  this->_Size = 2;
  this->_Timer= 0;
}

bool		Ship::SpriteAlive()
{
  if (this->_Old == 0)
    return (false);
  return (true);
}

Ship::~Ship()
{

}

void		Ship::CheckEtat(Move move, int x, int y)
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

void		Ship::CheckSize(int time)
{
  this->_EllapsedTime += time;
  switch (this->_Size)
    {
    case 1:
      {
	if (this->_EllapsedTime >= this->_FrameTime)
	  {
	    if (this->_Status == 11)
	      this->_Old = 0;
	    this->_Status += 1;
	    this->_EllapsedTime = 0;
	  }
      }
    case 2:
      {
	if (this->_EllapsedTime >= this->_FrameTime)
	  {
	    if (this->_Status == 6)
	      this->_Old = 0;
	    this->_Status += 1;
	    this->_EllapsedTime = 0;
	  }
      }
    case 3:
      {
	if (this->_EllapsedTime >= this->_FrameTime)
	  {
	    if (this->_Status == 3)
	      this->_Old = 0;
	    this->_Status += 1;
	    this->_EllapsedTime = 0;
	  }
      }
    }
}

void		Ship::FirstState(int time, Inputs inp)
{
	this->_Timer += time;
	this->_Timer2 += time;
  this->_EllapsedTime += time;
  if (this->_EllapsedTime >= this->_FrameTime)
    {
      this->CheckInputs(inp);
      this->_EllapsedTime = 0;
    }
}

void		Ship::GetSprite(int x, int y, Inputs inp, int time, Move move)
{
  this->_X = x;
  this->_Y = y;
  if (this->_Etat == 1)
    this->CheckEtat(move, x, y);
  if (this->_Etat == 1)
    this->FirstState(time, inp);
  else
    this->CheckSize(time);
}

void	Ship::CheckLeftAndRight()
{
	switch (this->_Status)
    {
    case 0:
      {
	this->_Status = 1;
	break;
      }
    case 1:
      {
	this->_Status = 2;
	break;
      }
    case 2:
      {
	this->_Status = 2;
	break;
      }
    case 3:
      {
	this->_Status = 2;
	break;
      }
    case 4:
      {
	this->_Status = 3;
      }
    }
}

void	Ship::CheckTop()
{
	this->_Timer = 0;
  switch(this->_Status)
    {
    case 0:
      {
	this->_Status = 1;
	break;
      }
    case 1:
      {
	this->_Status = 2;
	break;
      }
    case 2:
      {
	this->_Status = 3;
	break;
      }
    case 3:
      {
	this->_Status = 4;
	break;
      }
    case 4:
      {
	this->_Status = 4;
	break;
      }
    }
}

void	Ship::CheckDown()
{
	this->_Timer2 = 0;
  switch(this->_Status)
    {
    case 0:
      {
	this->_Status = 0;
	break;
      }
    case 1:
      {
	this->_Status = 0;
	break;
      }
    case 2:
      {
	this->_Status = 1;
	break;
      }
    case 3:
      {
	this->_Status = 2;
	break;
      }
    case 4:
      {
	this->_Status = 3;
	break;
      }
    }
}

void	Ship::CheckNothing()
{
  switch(this->_Status)
    {
    case 0:
      {
			  if (this->_Timer2 > 500)
			  {
				  this->_Status = 1;
				  this->_Timer2 = 0;
			  }
	break;
      }
    case 1:
      {
			  if (this->_Timer2 > 500)
			  {
				  this->_Status = 2;
				  this->_Timer2 = 0;
			  }
	break;
      }
    case 2:
      {
	this->_Status = 2;
	break;
      }
    case 3:
      {
		  if (this->_Timer > 500)
		  {
			  this->_Status = 2;
			  this->_Timer = 0;
		  }
	break;
      }
    case 4:
      {
			  if (this->_Timer > 500)
			  {
				  this->_Status = 3;
				  this->_Timer = 0;
			  }
	
	break;
      }
    }
}

void	Ship::CheckInputs(Inputs inp)
{
  switch(inp) 
    {
    case LEFT:
      this->CheckLeftAndRight();
      break;
    case RIGHT: 
      this->CheckLeftAndRight();
      break; 
    case TOP:
      this->CheckTop();
      break;
    case DOWN: 
      this->CheckDown();
      break;
    case NOTHING:
      this->CheckNothing();
    }
}

unsigned char Ship::getType()
{
  return (this->_Type);
}

int		Ship::getId()
{
  return (this->_Id);
}

int		Ship::getX()
{
  return (this->_X);
}

int		Ship::getY()
{
  return (this->_Y);
}

Inputs		Ship::getInput()
{
  return (this->_Inputs);
}

void		Ship::setInput(Inputs inp)
{
  this->_Inputs = inp;
}

int		Ship::GetEtat()
{
  return (this->_Etat);
}

int		Ship::GetStatus()
{
  return (this->_Status);
}

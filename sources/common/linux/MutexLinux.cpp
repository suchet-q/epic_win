//
// MutexLinux.cpp for zizi in /home/suchet_q//tek3/rtype/mutex
// 
// Made by quentin suchet
// Login   <suchet_q@epitech.net>
// 
// Started on  Wed Nov  6 00:53:36 2013 quentin suchet
// Last update Wed Nov 13 03:02:14 2013 geoffrey michelini
//

#include		"linux/MutexLinux.h"

MutexLinux::MutexLinux() : _init(false) {}

MutexLinux::~MutexLinux() {}

bool			MutexLinux::initMutex()
{
  if (pthread_mutex_init(&this->_mutex, NULL))
    return false;
  this->_init = true;
  return true;
}

bool			MutexLinux::Lock()
{
  if (!this->_init)
    return false;
  if (pthread_mutex_lock(&this->_mutex))
    return false;
  return true;
}

bool			MutexLinux::Unlock()
{
  if (!this->_init)
    return false;
  if (pthread_mutex_unlock(&this->_mutex))
    return false;
  return true;
}

bool			MutexLinux::destroyMutex()
{
  if (!this->_init)
    return false;
  if (pthread_mutex_destroy(&this->_mutex))
    return false;
  this->_init = false;
  return true;
}


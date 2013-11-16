/*
** MutexLinux.h for zizi in /home/suchet_q//tek3/rtype/mutex
** 
** Made by quentin suchet
** Login   <suchet_q@epitech.net>
** 
** Started on  Wed Nov  6 00:53:40 2013 quentin suchet
** Last update Wed Nov  6 00:56:04 2013 quentin suchet
*/

#pragma once

#include		<pthread.h>

class			MutexLinux
{
  pthread_mutex_t	_mutex;
  bool			_init;

 public:
  MutexLinux();
  ~MutexLinux();
  bool			initMutex();
  bool			Lock();
  bool			Unlock();
  bool			destroyMutex();
};

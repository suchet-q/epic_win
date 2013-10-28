//
// Threader.hpp for Threader in /home/bozzan_a//plazza
// 
// Made by adrien bozzano
// Login   <bozzan_a@epitech.net>
// 
// Started on  Fri Apr 12 15:08:49 2013 adrien bozzano
// Last update Tue Oct 22 09:51:37 2013 quentin suchet
//

#ifndef THREADER_HPP__
# define THREADER_HPP__

# include <iostream>
# include <pthread.h>
# include <signal.h>

#define		JOIN_ERROR (-1337)

template <typename T>
void*		funct(void *ptr);

template <typename S>
class		ThreaderLinux
{
  int		(T::*_ptr)(S *);
  pthread_t	_thread;
  T		*_inst;
  S		*_var;

public:
  ThreaderLinux()
  {
  }
  ~ThreaderLinux()
  {
  }

  void		*getPthread() const
  {
    return &this->_thread;
  }

  bool		start(int (T::*ptr)(S *), T *inst, S *var)
  {
    this->_ptr = ptr;
    this->_inst = inst;
    this->_var = var;
    if (pthread_create(&this->_thread, NULL, funct<ThreaderLinux<T, S> >, this) != 0)
      return false;
    return true;
  }

  int		launch()
  {
    return ((this->_inst->*_ptr)(this->_var));
  }

  int		waitThread()
  {
    void	*ret;

    if (pthread_join(this->_thread, &ret) != 0)
      return (JOIN_ERROR);
    return (*(reinterpret_cast<int *>(ret)));
  }

  bool		isAlive()
  {
    union sigval test;
    if (pthread_sigqueue(this->_thread, 0, test) != 0)
      return false;
    return true;
  }

  bool		killThread()
  {
    if (pthread_cancel(this->_thread) != 0)
      return false;
    return true;
  }

  void		exit()
  {
    pthread_exit(NULL);
  }
};

template <typename T>
void*		funct(void *ptr)
{
  T		*c = reinterpret_cast<T *>(ptr);
  int		*res = new int();

  *res = c->launch();
  return (reinterpret_cast<void *>(res));
}

#endif

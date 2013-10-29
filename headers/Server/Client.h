//
// Client.h for airtype in /home/michel_b//epic_win
// 
// Made by geoffrey michelini
// Login   <michel_b@epitech.net>
// 
// Started on  Tue Oct 29 20:08:52 2013 geoffrey michelini
// Last update Tue Oct 29 20:19:08 2013 geoffrey michelini
//


#ifndef			__CLIENT_H__
# define		__CLIENT_H__

class			Client
{
private:
  MetaSocket		_socketTCP;

public:
  MetaSocket	const	&getSocketTCP();
};

#endif

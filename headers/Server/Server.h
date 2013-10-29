//
// Server.h for airtype in /home/michel_b//Airtype
// 
// Made by geoffrey michelini
// Login   <michel_b@epitech.net>
// 
// Started on  Mon Oct 28 18:21:08 2013 geoffrey michelini
// Last update Tue Oct 29 22:11:03 2013 geoffrey michelini
//

#ifndef			__SERVER_H__
# define		__SERVER_H__

# include		<iostream>
# include		<string>
# include		<list>

# include		"MetaSocket.h"
# include		"StructCommands.h"

class			Server
{
private:
  MetaSocket<>			_socket;

public:
  Server();
  ~Server();

  bool			initSocket(int port);
  bool			loop();

  void			execPND(void *command, int size);
  void			execNBP(void *command, int size);
  void			execNBL(void *command, int size);
  void			execJNL(void *command, int size);
  void			execCRL(void *command, int size);
  void			execPLJ(void *command, int size);
  void			execSTL(void *command, int size);
  void			execMSG(void *command, int size);
  void			execNMP(void *command, int size);
  void			execLVL(void *command, int size);
};

#endif

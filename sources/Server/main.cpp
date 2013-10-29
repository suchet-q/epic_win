//
// main.cpp for airtype in /home/michel_b//epic_win
// 
// Made by geoffrey michelini
// Login   <michel_b@epitech.net>
// 
// Started on  Tue Oct 29 21:28:45 2013 geoffrey michelini
// Last update Tue Oct 29 22:11:03 2013 geoffrey michelini
//

#include	<sstream>
#include	"Server.h"

int		main(int ac, char **av)
{
  std::istringstream	buffer;
  Server	server;
  int		port;

  if (ac < 2) {
    std::cerr << "[USAGE]: R-type [PORT]" << std::endl;
    return (-1);
  }
  buffer.str(av[1]);
  buffer >> port;
  if (!server.initSocket(port))
    return (-1);
  return (0);
}

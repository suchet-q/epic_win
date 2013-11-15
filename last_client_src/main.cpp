#include	<iostream>
#include	<SFML/System.hpp>
#include	"Client.h"


int		main(int ac, char **av)
{
	Client	client;
	
	if (ac < 3)
		client.launch("127.0.0.1", 4242);
	else
		if (client.launch(/*"127.0.0.1", 4242*/av[1], atoi(av[2])) == false)
			return (-1);
	return (0);
}


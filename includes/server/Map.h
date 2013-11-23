#pragma once

# include		<sstream>
# include		<fstream>
# include		<string>

# include		"Coord.hpp"
# include		"Entities.h"

struct			t_spawn
{
  entityType		type;
  unsigned short int	y;
  unsigned long int		time;
};

class			Map
{
private:
  std::list<t_spawn>	_spawnList;

public:
  Map();
  ~Map();

  std::list<t_spawn>&	getSpanList();

  bool			parseMap(std::string const &filename);
};

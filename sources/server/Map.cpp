#include		"Map.h"
#include		<iostream>

Map::Map() {}

Map::~Map() {}

std::list<t_spawn>&	Map::getSpanList() {
  return (this->_spawnList);
}

bool			Map::parseMap(std::string const &filename)
{
  std::ifstream		file;
  std::stringstream	ss;
  std::string	line;
  t_spawn		tmp;
  std::string	step;
  int			value;
  int			i = 0;
  entityType	entity;

  file.open(filename, std::ifstream::in);
  if (!file.good()) 
    return false;
  if (file.peek() == std::ifstream::traits_type::eof())
	  return true;

  int	letter;
  std::string	step2;

  while (!file.eof()) 
  {
	std::getline(file, line);

	ss.str("");
	ss.clear();
	letter = line.find(' ');
	step = line.substr(0, letter);
	ss.str(step);
	ss >> i;
	tmp.type = static_cast<entityType>(i);

	ss.str("");
	ss.clear();
	step2 = line.substr(letter + 1, line.size());
	letter = step2.find(' ');
	step = step2.substr(0, letter);
	ss.str(step);
	ss >> tmp.y;

	ss.str("");
	ss.clear();
	letter += step2.find(' ');
	step = line.substr(letter, line.size());
	ss.str(step);
	ss >> tmp.time;
	this->_spawnList.push_back(tmp);
  } 
  return true;
}

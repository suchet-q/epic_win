#include		"Map.h"

Map::Map() {}

Map::~Map() {}

std::list<t_spawn>&	Map::getSpanList() {
  return (_spawnList);
}

bool			Map::parseMap(std::string const &filename)
{
  std::ifstream		file;
  std::istringstream	iss;
  char			buffer[512];
  t_spawn		tmp;
  int			value;
  int			i = 0;

  file.open(filename);
  if (!file.good()) 
    return false;
  
  while (!file.eof()) {
    file.getline(buffer, 511, ' ');
    iss.get(buffer, 512, '\0');
    iss >> value;
    switch (i) {
    case 0 :
      tmp.type = static_cast<entityType>(value);
      break;
    case 1 :
      tmp.y = value;
      break;
    case 3 :
      tmp.time = value;
      _spawnList.push_back(tmp);
      i = 0;
      break;
    }
  } 
  return true;
}

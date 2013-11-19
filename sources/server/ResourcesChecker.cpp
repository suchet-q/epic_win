#include "ResourcesChecker.h"


ResourcesChecker::ResourcesChecker()
{
	this->_typeMap[0] = ALIEN;
	this->_typeMap[1] = BALLS;
	this->_typeMap[2] = BIG_SHOT;
	this->_typeMap[3] = BIGGEST_SHOT;
	this->_typeMap[4] = FIREBALL;
	this->_typeMap[5] = MEDIUM_SHOT;
	this->_typeMap[6] = BASIC_SHOT;
	this->_typeMap[7] = DOG;
	this->_typeMap[8] = DRONE;
	this->_typeMap[9] = JUMPER;
	this->_typeMap[10] = METROID;
	this->_typeMap[11] = PLAYER1;
	this->_typeMap[12] = XWING;
	this->_name.push_back("Alien.txt");
	this->_name.push_back("bonus.txt");
	this->_name.push_back("bullet_big.txt");
	this->_name.push_back("bullet_biggest.txt");
	this->_name.push_back("bullet_enemy_basis.txt");
	this->_name.push_back("bullet_medium.txt");
	this->_name.push_back("bullets_small.txt");
	this->_name.push_back("Dog.txt");
	this->_name.push_back("Drone.txt");
	this->_name.push_back("Jumper.txt");
	this->_name.push_back("Metroid.txt");
	this->_name.push_back("Ship.txt");
	this->_name.push_back("Xwing");
}


ResourcesChecker::~ResourcesChecker() {}

std::map<entityType, t_tab_hit_box>		&ResourcesChecker::getFileResources()
{
	std::ifstream	file;
	t_tab_hit_box			tmpHit;
	int	i;
	int	j;
	std::string				line;
	std::stringstream		ss;

	j = 0;
	for (std::list<std::string>::iterator it = this->_name.begin();
		it != this->_name.end(); ++it)
	{
		file.open((*it), std::ifstream::in);
		if (!file.is_open())
			throw new std::exception("Can't open file colision");
		tmpHit.x = 0;
		tmpHit.y = 0;
		tmpHit.yStart = 0;
		i = 1;
		while (file.eof() != false && i <= 3)
		{
			file >> line;
			ss << line;
			if (i == 1)
				ss >> tmpHit.x;
			else if (i == 2)
				ss >> tmpHit.y;
			else
				ss >> tmpHit.yStart;
			++i;
		}
		if (i != 4)
			throw new std::exception("Error : file Colision corrupted");
		tmpHit.tab = new char*[tmpHit.y];
		i = 0;
		while (file.eof())
		{
			tmpHit.tab[i] = new char[tmpHit.x];
			file >> line;
			if (line.size() != tmpHit.x)
				throw new std::exception("Error : file Colision corrupted");
			memcpy(tmpHit.tab[i], line.c_str(), line.size());
			++i;
		}
		if ((i + 1) != tmpHit.y)
			throw new std::exception("Error : file Colision corrupted");
		this->_tmp[this->_typeMap[j]] = tmpHit;
		++j;
	}
	return (this->_tmp);
}
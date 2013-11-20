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
	this->_typeMap[13] = KIKOU_SHOT;
	this->_typeMap[14] = MONSTER;
	this->_typeMap[15] = MONSTER_REVERT;
	this->_typeMap[16] = BIDULE;
	this->_typeMap[17] = BIDULE_REVERT;
	this->_typeMap[18] = PLATFORM;
	this->_typeMap[19] = PLATFORM_REVERT;
	this->_typeMap[20] = PLATFORM2;
	this->_typeMap[21] = PLATFORM2_REVERT;
	this->_name.push_back("collisionTab/Alien.txt");
	this->_name.push_back("collisionTab/bonus.txt");
	this->_name.push_back("collisionTab/bullet_big.txt");
	this->_name.push_back("collisionTab/bullet_biggest.txt");
	this->_name.push_back("collisionTab/bullet_enemy_basis.txt");
	this->_name.push_back("collisionTab/bullet_medium.txt");
	this->_name.push_back("collisionTab/bullets_small.txt");
	this->_name.push_back("collisionTab/Dog.txt");
	this->_name.push_back("collisionTab/Drone.txt");
	this->_name.push_back("collisionTab/Jumper.txt");
	this->_name.push_back("collisionTab/Metroid.txt");
	this->_name.push_back("collisionTab/Ship.txt");
	this->_name.push_back("collisionTab/Xwing.txt");
	//this->_name.push_back("collisionTab/bullet_kikou.txt");
	this->_name.push_back("collisionTab/monster.txt");
	this->_name.push_back("collisionTab/monster_revert.txt");
	this->_name.push_back("collisionTab/bibule.txt");
	this->_name.push_back("collisionTab/bidule_revert.txt");
	this->_name.push_back("collisionTab/platform.txt");
	this->_name.push_back("collisionTab/platform_revert.txt");
	this->_name.push_back("collisionTab/platform2.txt");
	this->_name.push_back("collisionTab/platform2_revert.txt");
}


ResourcesChecker::~ResourcesChecker() {}

std::map<entityType, t_tab_hit_box>		&ResourcesChecker::getFileResources()
{
	std::ifstream	file;
	t_tab_hit_box	tmpHit;
	unsigned int	i;
	unsigned int	j;
	std::string				line;
	std::stringstream		ss;

	j = 0;
	for (std::list<std::string>::iterator it = this->_name.begin();
		it != this->_name.end(); ++it)
	{
		file.open((*it).c_str(), std::ifstream::in);
		if (!file.is_open())
			throw new std::exception("Can't open file colision");
		tmpHit.x = 0;
		tmpHit.y = 0;
		tmpHit.yStart = 0;
		i = 1;
		while (!file.eof() != false && i <= 3)
		{
			std::getline(file, line);
			ss.str("");
			ss.clear();
			ss.str(line);
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
		while (!file.eof() && i < tmpHit.y)
		{
			tmpHit.tab[i] = new char[tmpHit.x];
			std::getline(file, line);
			if (line.size() != tmpHit.x)
				throw new std::exception("Error : file Colision corrupted");
			memcpy(tmpHit.tab[i], line.c_str(), line.size());
			++i;
		}
		if (i != tmpHit.y)
			throw new std::exception("Error : file Colision corrupted");
		this->_tmp[this->_typeMap[j]] = tmpHit;
		++j;
		for (unsigned int t = 0; t < tmpHit.y; ++t)
		{
			for (unsigned int k = 0; k < tmpHit.x; ++k)
				this->_tmp[this->_typeMap[j - 1]].tab[t][k] -= '0';
		}
		file.close();
	}
	return (this->_tmp);
}

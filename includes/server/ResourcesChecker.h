#pragma once

#include	<fstream>
#include	<map>
#include	<sstream>
#include	<string>
#include	<iostream>
#include	<cstring>
#include	<exception>
#include	<stdexcept>
#include	"Entities.h"

struct		t_tab_hit_box
{
	char**		tab;
	unsigned int			x;
	unsigned int			y;
	unsigned int			yStart;
};

class ResourcesChecker
{
private:
	std::map<entityType, t_tab_hit_box> _tmp;
	std::map<int, entityType> _typeMap;
	std::list<std::string>	_name;
public:
	ResourcesChecker();
	~ResourcesChecker();
	std::map<entityType, t_tab_hit_box>		&getFileResources();
};


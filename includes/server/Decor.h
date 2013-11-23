#pragma once
#include	"Entities.h"

class Decor : public Entity
{
public:
	Decor();
	~Decor();
	void			update(std::list<Entity *> &);
};


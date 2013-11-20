#include "Jumper.h"

Jumper::Jumper() {}

Jumper::~Jumper() {}

bool		Jumper::update(std::list<Entity *> &)
{
	float	vecY;

	vecY = this->_sinus.getValue(this->_coord);
	/*for new  vec_coord call this->_sinus.calculNewVecX(x)
	and this->_sinus.calculNewVecY(y, vecY)*/
	if (this->getInput() == 0)
		this->setInput(LEFT);
	return (true);
}

extern "C"
#ifdef _WIN32
__declspec (dllexport)
#endif
Entity		*getInstance()
{
	return new Jumper();
}
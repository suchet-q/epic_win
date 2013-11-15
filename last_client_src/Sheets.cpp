#include "Sheets.h"


Sheets::Sheets(void)
{
}


Sheets::~Sheets(void)
{
	for (std::map<int, std::list<Callback *> >::iterator it = this->_callback.begin(); it != this->_callback.end(); ++it)
		for (std::list<Callback *>::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2)
		delete (*it2);
}

void		Sheets::setSheetPointer(int *sheetNb)
{
	this->_sheetNb = sheetNb;
}

void		Sheets::setActualSheet(int sheet)
{
	std::list<Callback *>::iterator		it;

	(*this->_sheetNb) = sheet;
	for (it = this->_callback[sheet].begin(); it != this->_callback[sheet].end(); ++it)
		(*it)->triggerCallback();
}


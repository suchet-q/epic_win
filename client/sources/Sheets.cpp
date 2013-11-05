#include "Sheets.h"


Sheets::Sheets(void)
{
}


Sheets::~Sheets(void)
{
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

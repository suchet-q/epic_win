#pragma once
#include	<iostream>
#include	<map>
#include	<list>
#include	"Callback.hpp"

class AWidget;

class Sheets
{
	int										_actualSheet;
	int*									_sheetNb;
	std::map<int, std::list<Callback *> >	_callback;
public:
	Sheets(void);
	~Sheets(void);

	void	setActualSheet(int);
	void	setSheetPointer(int*);
	template <typename T>
	void	addWidgetToSheet(int sheet, T *ref, void (T::*method)()) {
		this->_callback[sheet].push_back(new CallbackT<T>(ref, method));
	}
};


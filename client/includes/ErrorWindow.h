#pragma once
#include	<list>
#include	"RenderWindow.h"
#include	"WidgetText.h"

class ErrorWindow : public RenderWindow
{
	WidgetText		_msg;
	WidgetText		_method;
public:
	ErrorWindow(void);
	virtual ~ErrorWindow(void);

	void		displayError(const std::string &, const std::string &);
	void		initialize();
};


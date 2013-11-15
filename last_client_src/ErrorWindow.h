#pragma once
#include	<list>
#include	"RenderWindow.h"
#include	"WidgetText.h"
#include	"WidgetButton.h"

class ErrorWindow : public RenderWindow
{
	WidgetText		_msg;
	WidgetText		_method;
	WidgetButton	_ok;
public:
	ErrorWindow(void);
	virtual ~ErrorWindow(void);

	virtual void	handleEvents();
	void		displayError(const std::string &, const std::string &);
	void		initialize();
};


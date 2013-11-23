#pragma once

#define		WIN_X 1024
#define		WIN_Y 768

#define		SP_POS	1
#define		SP_TRS	2
#define		SP_SCL	4
#define		SP_ROT	8

#define		CMD_PNB		0
#define		CMD_NBP		1
#define		CMD_NBL		2
#define		CMD_JNL		3
#define		CMD_CRL		4
#define		CMD_PLJ		5
#define		CMD_STL		6
#define		CMD_MSG		7
#define		CMD_NMP		8
#define		CMD_LVL		9
#define		CMD_AFF		10
#define		CMD_SCR		11
#define		CMD_LIF		12
#define		CMD_EVT		13
#define		CMD_INP		14
#define		CMD_IDT		15
#define		INP_LEFT	1
#define		INP_RIGHT	2
#define		INP_UP		4
#define		INP_DOWN	8
#define		INP_FIRE	16

#ifdef _WIN32

#define		THREADS_INITIALISATION		;
#define		MUT_LOCK	;
#define		MUT_UNLOCK	;

#else

/* #include	<X11/Xlib.h> */
#define		THREADS_INITIALISATION	XInitThreads();
#define		MUT_LOCK	this->_mutex.lock();
#define		MUT_UNLOCK	this->_mutex.unlock();

#endif



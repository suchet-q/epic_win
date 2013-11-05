#pragma once

#include	<boost/bind.hpp>
#include	<boost/function.hpp>
#include	<boost/any.hpp>
#include	<list>
#include	<map>
#include	"Macros.h"
#include	"StructCommands.h"

typedef boost::function<boost::any (std::list<boost::any>)> cFunctor;

class Parser
{
	std::map<unsigned char, std::list<cFunctor> >		_callbacks;
	std::map<unsigned char, void (Parser::*)(void *, int)>	_functions;
	std::list<std::pair<void *, int> >						_queued;
	char													_cmd[512];
	int														_cmdSize;
	std::map<unsigned char, int>							_castArray;

	void		parsePNB(void *, int);
	void		parseNBP(void *, int);
	void		parseNBL(void *, int);
	void		parseJNL(void *, int);
	void		parseCRL(void *, int);
	void		parsePLJ(void *, int);
	void		parseSTL(void *, int);
	void		parseMSG(void *, int);
	void		parseNMP(void *, int);
	void		parseLVL(void *, int);
	void		parseAFF(void *, int);
	void		parseSCR(void *, int);
	void		parseLIF(void *, int);
	void		parseEVT(void *, int);
public:
	Parser();
	~Parser();
	void		parse(void *, int);
	void		addCallback(unsigned char, cFunctor);
	std::pair<void *, int>	getQueued();
	void		addNBL();
	void		addNBP();
	void		addJNL(unsigned char, unsigned char);
	void		addCRL(unsigned char);
	void		addNMP(unsigned char, std::string const &);
	void		addMSG(unsigned char, unsigned char, std::string const &);
	void		addLVL(unsigned char, unsigned char);
	void		addINP(unsigned char, unsigned short);
	void		addIDT(unsigned char);
};


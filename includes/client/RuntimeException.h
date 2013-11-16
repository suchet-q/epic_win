#pragma once
#include	<exception>
#include	<stdexcept>

class RuntimeException : public std::runtime_error
{
	std::string		_method;
public:
	RuntimeException() : runtime_error("") {}
	RuntimeException(const std::string &method, const std::string &str) : runtime_error(str) { this->_method = method; }
	virtual ~RuntimeException(void) throw () {}

	virtual const char * what() const throw() { return (runtime_error::what()); }
	virtual const std::string &			method() { return(this->_method); }
};

class MinorException : public RuntimeException
{
public:
	MinorException() : RuntimeException() {}
	MinorException(const std::string &method, const std::string &str) : RuntimeException(method, str) {}
  //~MinorException() {}
};


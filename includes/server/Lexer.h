#pragma once
#include		<iostream>
#include		<string>
#include		"StructCommands.h"

class			Lexer
{
public:
	Lexer();
	~Lexer();
	template<typename R/*retour*/, typename I/*instence*/, typename A/*args*/, typename S/*size*/>
	void		callCommand(A *command, R (I::**ptr)(A*), I *instance, S size)
	{
		(instance->*ptr[reinterpret_cast<char *>(command)[0]])(command, size);
	}
};
##
## Makefile for airtype in /home/michel_b//Airtype
## 
## Made by geoffrey michelini
## Login   <michel_b@epitech.net>
## 
## Started on  Mon Oct 28 18:55:47 2013 geoffrey michelini
## Last update Tue Nov 12 00:13:50 2013 geoffrey michelini
##


NAME_SERVER=	R-type

NAME_CLIENT=	client

SRC_SERVER=	sources/Server/main.cpp					\
		sources/Server/Server.cpp				\
		sources/Server/Lexer.cpp				\
		sources/Server/Client.cpp				\
		sources/Server/Room.cpp					\
		sources/Server/Executer.cpp				\
		sources/Server/Network.cpp				\
		sources/Server/Resource.cpp				\
		sources/Server/Game.cpp					\
		sources/Server/ResourcesGame.cpp			\
		sources/Server/Entity.cpp				\
		sources/Server/Ship.cpp					\
		sources/Server/Shot.cpp					\
		sources/Abstraction/Linux/LoadLibLinux.cpp		\
		sources/Abstraction/Linux/SocketLinux.cpp		\
		sources/Abstraction/Linux/SelectLinux.cpp
SRC_CLIENT=

OBJ_SERVER=	$(SRC_SERVER:.cpp=.o)

OBJ_CLIENT=	$(SRC_CLIENT:.cpp=.o) 

CPP=		g++

CXXFLAGS=	-I./headers/Abstraction -I./headers/Server -I./headers/Client -I./headers/Graphic	\
		-ldl -std=c++0x -Wall -Wextra

all:		$(NAME_SERVER)	\
		$(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER)
		$(CPP) $(CXXFLAGS) $(OBJ_SERVER) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT)
		$(CPP) $(CXXFLAGS) $(OBJ_CLIENT) -o $(NAME_CLIENT)

clean:
		rm -rf $(OBJ_SERVER) 
		rm -rf $(OBJ_CLIENT)

fclean:		clean
		rm -rf $(NAME_SERVER)
		rm -rf $(NAME_CLIENT)

re:		fclean all
##
## Makefile for airtype in /home/michel_b//Airtype
## 
## Made by geoffrey michelini
## Login   <michel_b@epitech.net>
## 
## Started on  Mon Oct 28 18:55:47 2013 geoffrey michelini
## Last update Mon Oct 28 19:34:02 2013 geoffrey michelini
##


NAME_SERVER=	airtype

NAME_CLIENT=	client

NAME_GRAPHIC=	graphic

SRC_SERVER=	sources/Server/main.cpp					\
		sources/Server/Server.cpp				\
		sources/Abstraction/Linux/LoadLibLinux.cpp		\
		sources/Abstraction/Linux/SocketLinux.cpp
SRC_CLIENT=

SRC_GRAPHIC=

OBJ_SERVER=	$(SRC_SERVER:.cpp=.o)

OBJ_GRAPHIC=	$(SRC_GRAPHIC:.cpp=.o)

OBJ_CLIENT=	$(SRC_CLIENT:.cpp=.o) 

CPP=		g++

CXXFLAGS=	-I./headers/Abstraction -I./headers/Server -I./headers/Client -I./headers/Graphic	\
		-ldl

all:		$(NAME_SERVER)	\
		$(NAME_CLIENT)	\
		$(NAME_GRAPHIC)

$(NAME_SERVER): $(OBJ_SERVER)
		$(CPP) $(CXXFLAGS) $(OBJ_SERVER) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT)
		$(CPP) $(CXXFLAGS) $(OBJ_CLIENT) -o $(NAME_CLIENT)

$(NAME_GRAPHIC):$(OBJ_GRAPHIC)
		$(CPP) $(CXXFLAGS) $(OBJ_GRAPHIC) -o $(NAME_GRAPHIC)

clean:
		rm -rf $(OBJ_SERVER) 
		rm -rf $(OBJ_CLIENT)
		rm -rf $(OBJ_GRAPHIC)

fclean:		clean
		rm -rf $(NAME_SERVER)
		rm -rf $(NAME_CLIENT)
		rm -rf $(NAME_GRAPHIC)

re:		fclean all
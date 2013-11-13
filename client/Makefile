##
## Makefile for Makefile in /home/blery_g//WORK/RTYPE
## 
## Made by gaetan blery
## Login   <blery_g@epitech.net>
## 
## Started on  Tue Nov  5 04:51:21 2013 gaetan blery
## Last update Wed Nov 13 03:51:02 2013 geoffrey michelini
##

NAME=	r-type

SRC=	sources/AWidget.cpp \
	sources/Client.cpp \
	sources/ErrorWindow.cpp \
	sources/GameMenu.cpp \
	sources/GameSocket.cpp \
	sources/main.cpp \
	sources/Parser.cpp \
	sources/RenderWindow.cpp \
	sources/SelectLinux.cpp \
	sources/Sheets.cpp \
	sources/SocketLinux.cpp \
	sources/SoundPool.cpp \
	sources/Sprite.cpp \
	sources/WidgetButton.cpp \
	sources/WidgetImage.cpp \
	sources/WidgetSwitch.cpp \
	sources/WidgetText.cpp \
	sources/WidgetTypingBar.cpp


OBJ=	$(SRC:.cpp=.o)

GCC=	g++ -W -Wall -Werror -Wextra

CXXFLAGS=	-I./includes -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-window

all:	$(NAME)

$(NAME):	$(OBJ)
	$(GCC) $(OBJ) $(CXXFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all
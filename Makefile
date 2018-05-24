NAME = avm
CC = clang++
CPPFLAGS = -Wall -Wextra -Werror -std=c++11

OBJECTS =   main.o \
			Lexer.o \
			LexerException.o \

.PHONY : clean all fclean re

all : $(NAME)
	
$(NAME) : $(OBJECTS)
	$(CC) $(CPPFLAGS) -o $(NAME) $(OBJECTS)

clean :
	rm -rf $(OBJECTS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

main.o : main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

Lexer.o : Lexer.cpp
	$(CC) $(CPPFLAGS) -c Lexer.cpp

LexerException.o : LexerException.cpp
	$(CC) $(CPPFLAGS) -c LexerException.cpp
	
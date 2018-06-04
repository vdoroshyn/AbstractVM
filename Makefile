NAME = avm
CC = clang++
CPPFLAGS = -Wall -Wextra -Werror -std=c++11

OBJECTS =   main.o \
			Lexer.o \
			Parser.o \
			VirtualMachine.o \
			LexerException.o \
			ParserException.o \
			VirtualMachineException.o \
			OperandFactory.o \

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

Parser.o : Parser.cpp
	$(CC) $(CPPFLAGS) -c Parser.cpp

VirtualMachine.o : VirtualMachine.cpp
	$(CC) $(CPPFLAGS) -c VirtualMachine.cpp

LexerException.o : LexerException.cpp
	$(CC) $(CPPFLAGS) -c LexerException.cpp

ParserException.o : ParserException.cpp
	$(CC) $(CPPFLAGS) -c ParserException.cpp

VirtualMachineException.o : VirtualMachineException.cpp
	$(CC) $(CPPFLAGS) -c VirtualMachineException.cpp

OperandFactory.o : OperandFactory.cpp
	$(CC) $(CPPFLAGS) -c OperandFactory.cpp

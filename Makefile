NAME = avm
CC = clang++
CPPFLAGS = -Wall -Wextra -Werror

OBJECTS = main.o \

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

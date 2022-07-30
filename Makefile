##
## EPITECH PROJECT, 2022
## B-SYN-400-MPL-4-1-abstractVM-noe.sellam
## File description:
## Makefile
##

CC = g++

NAME = abstractVM
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

CFLAGS = -W -Wall -Wextra -I./include

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re:		fclean all
		rm -f $(OBJ)

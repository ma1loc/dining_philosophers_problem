CC = cc
CFLAGS = -Wall -Wextra Werror
SRC = philo.c
OBJ = $(src:.c = .o)
NAME = philo

all: $(NAME)

$(OBJ): $(SRC)
	
CC=cc
INCLUDE = -Isrcs
CFLAGS=-Wall -Wextra -Werror $(INCLUDE)
SRC=srcs/_philo.c philo_parsing/ft_atoi.c philo_parsing/input_validation.c philo_utils/ft_strlen.c philo_utils/ft_putstr_fd.c philo_utils/gc_malloc.c \
	philo_utils/cleanup_and_exit.c
OBJ=$(SRC:.c=.o)
NAME=philo
RM=rm -rf
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re


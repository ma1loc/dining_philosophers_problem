CC=cc
INCLUDE = -Isrcs
CFLAGS=-Wall -Wextra -Werror $(INCLUDE)

SRC=srcs/philo.c philo_utils/gc_manager.c philo_utils/cleanup_and_exit.c philo_parsing/ft_atoi.c \
	philo_parsing/ft_strlen.c philo_parsing/ft_putstr_fd.c philo_utils/get_time.c philo_utils/init_setup.c \
	philo_parsing/input_validation.c philo_utils/init_philo.c philo_utils/start_simulation.c \
	philo_utils/philo_routine.c philo_utils/monitor_routine.c philo_utils/monitor_utils.c \
	philo_utils/routine_utils.c

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


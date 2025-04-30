# ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

int	ft_atoi(const char *str);
int	input_parsing(int argc, char **argv);

typedef struct s_user_args
{
	int	nbr_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_meals;
}	t_user_args;


# endif
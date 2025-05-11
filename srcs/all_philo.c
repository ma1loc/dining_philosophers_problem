# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_mem
{
	void			*ptr;
	struct s_mem	*next;
}	t_mem;

typedef struct	s_gc
{
	t_mem			*mem_list;
	int				total_allocs;
	size_t			total_bytes;
}	t_gc;

typedef struct	s_user_args
{
	int	nbr_of_philo;	// >>> number of the philo (thread)
	int	time_to_die;	
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_meals;	// >>> option -> how much the phlos must eating
}	t_user_args;

typedef	struct	s_philo
{
	int				id;				// >>> just a number of the philo(X)
	int				eat_count;		// >>> track how much time take each philo to eat
	long			last_meal_time;	// >>> to get the last meal time. check it in every thread, in the first time have to set to 0, if the current time > time last_meal = dea
	pthread_t		thread;			// >>> hold id of the thread
	pthread_mutex_t	*left_fork;		// >>> left fork(thread) 
	pthread_mutex_t	*right_fork;	// >>> right fork(thread)
	pthread_mutex_t	*print_mutex;	// >>> ensures only one thread prints at a time.
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*death_mutex;
	int				*someone_died;
}	t_philo;

typedef struct s_setup
{
	t_gc			*gc;
	t_user_args		*user_args;
	t_philo			*philo;
	// >>>>>>>>>>>>>>>>>>>>>>>>
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;	// >>> ensures only one thread prints at a time.
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	int				someone_died;
	// >>>>>>>>>>>>>>>>>>>>>>>>
} t_setup;


void	is_valid_digits(char **argv, t_setup *setup)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		// printf("before argv[%d] -> %s\n", i, argv[i]);
		if (ft_atoi(argv[i], setup) <= 0)
			cleanup_and_exit(setup, "[-] Error:"\
			" args Not a valid number.\n", 1);
		i++;
	}
}

int	is_invalid_input(char *str)
{
	size_t	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i] && ((str[i] == ' ')
		|| (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (1);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] && ((str[i] == ' ')
		|| (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

void	input_parsing(int argc, char **argv, t_setup *setup)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		cleanup_and_exit(setup, "[-] Error:"\
		" Number of args not currect.\n", 1);
	while (argv[i])
	{
		if (is_invalid_input(argv[i]))
			cleanup_and_exit(setup, "[-] Error:"\
			" The args syntax not currect.\n", 1);
		i++;
	}
	is_valid_digits(argv, setup);
}

void	setup_user_args(t_setup *setup, char **argv)
{
	setup->user_args = gc_malloc(setup->gc, sizeof(t_user_args));
	if (!setup->user_args)
		cleanup_and_exit(setup, "[-] Error: malloc failed.\n", 1);	// use cleanup_and_exit
	setup->user_args->nbr_of_philo = ft_atoi(argv[1], setup);
	setup->user_args->time_to_die = ft_atoi(argv[2], setup);
	setup->user_args->time_to_eat = ft_atoi(argv[3], setup);
	setup->user_args->time_to_sleep = ft_atoi(argv[4], setup);
	setup->user_args->must_eat_meals = -1;
	if (argv[5])
		setup->user_args->must_eat_meals = ft_atoi(argv[5], setup);
}

void	init_philos(t_setup *setup)
{
	int	i;
	int	philo_nbr;
	
	philo_nbr = setup->user_args->nbr_of_philo;
	setup->forks = gc_malloc(setup->gc, (sizeof(pthread_mutex_t) * philo_nbr));
	setup->philo = gc_malloc(setup->gc, sizeof(t_philo) * philo_nbr);
	if (!setup->forks || !setup->philo)
		cleanup_and_exit(setup, "[-] Error: malloc failed.\n", 1);
	i = -1;
	while (++i < philo_nbr)
		pthread_mutex_init(&setup->forks[i], NULL);
	i = -1;
	while (++i < philo_nbr)
	{
		setup->philo[i].id = (i + 1);
		setup->philo[i].eat_count = 0;
		setup->philo[i].last_meal_time = 0;
		setup->philo[i].left_fork = &setup->forks[i];
		setup->philo[i].right_fork = &setup->forks[(i + 1) % philo_nbr];
		setup->philo[i].print_mutex = &setup->print_mutex;
		setup->philo[i].meal_mutex = &setup->meal_mutex;
		setup->philo[i].death_mutex = &setup->death_mutex;
		setup->philo[i].someone_died = &setup->someone_died;
	}
}

t_setup	*init_setup(int argc, char **argv)
{
	t_setup	*setup;
	t_gc	*gc;

	gc = gc_init();
	setup = gc_malloc(gc, sizeof(t_setup));
	if (!setup || !gc)
		return (cleanup_and_exit(setup, "[-] Error: malloc failed.\n", 1), NULL);
	memset(setup, 0, sizeof(t_setup));
	setup->gc = gc;						// >>> init gc
	input_parsing(argc, argv, setup);	// >>> parsing user input before init
	setup_user_args(setup, argv);		// >>> init user_args
	setup->start_time = get_time_ms();	// >>> init start time
	pthread_mutex_init(&setup->print_mutex, NULL);
	pthread_mutex_init(&setup->meal_mutex, NULL);
	pthread_mutex_init(&setup->death_mutex, NULL);
	setup->someone_died = 0;
	init_philos(setup);					// >>> init philo
	return (setup);
}

int	main(int argc, char **argv)
{
	t_setup	*setup;

	setup = init_setup(argc, argv);
	if (!setup)
		return (1);
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>
	// i stock here(i don't now what to do... fuck)
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>
	gc_destroy(setup->gc);
	return (0);
}
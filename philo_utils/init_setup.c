# include "philo.h"

int	setup_user_args(t_setup *setup, char **argv)
{
	setup->user_args = gc_malloc(setup->gc, sizeof(t_user_args));
	if (!setup->user_args)
		return (cleanup_and_exit(setup, "[-] Error: malloc failed.\n", 1), 1);
	setup->user_args->nbr_of_philo = ft_atoi(argv[1]);
	setup->user_args->time_to_die = ft_atoi(argv[2]);
	setup->user_args->time_to_eat = ft_atoi(argv[3]);
	setup->user_args->time_to_sleep = ft_atoi(argv[4]);
	setup->user_args->must_eat_meals = -1;
	if (argv[5])
		setup->user_args->must_eat_meals = ft_atoi(argv[5]);
	return (0);
}

t_setup	*init_setup(int argc, char **argv)
{
	t_setup	*setup;
	t_gc	*gc;

	gc = gc_init();
	setup = gc_malloc(gc, sizeof(t_setup));
	if (!gc || !setup)
		return (cleanup_and_exit(setup, "[-] Error: malloc failed.\n", 1), NULL);	// fixed
	setup->gc = gc;
	if (input_parsing(argc, argv, setup))	// check the fix
		return(NULL);
	setup->someone_died = 0;
	setup->all_ate_enough = 0;
	pthread_mutex_init(&setup->print_mutex, NULL);
	pthread_mutex_init(&setup->meal_mutex, NULL);
	pthread_mutex_init(&setup->death_mutex, NULL);
	if (setup_user_args(setup, argv))
		return (NULL);
	setup->start_time = get_time_ms();
	setup->user_args->start_time = setup->start_time;
	if (init_philos(setup))
		return (NULL);
	return (setup);
}

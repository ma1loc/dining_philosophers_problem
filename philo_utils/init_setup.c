# include "_philo.h"

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

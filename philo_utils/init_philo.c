# include "philo.h"

// done //

void set_philo_forks(t_setup *setup, int i)
{
    int philo_nbr;
    
    philo_nbr = setup->user_args->nbr_of_philo;
    if (philo_nbr == 1)
    {
        setup->philo[i].left_fork = &setup->forks[0];
        setup->philo[i].right_fork = NULL;
    }
    else
    {
        // Always assign left fork as the philosopher's index
        // and right fork as the next philosopher's index (wrapping around)
        setup->philo[i].left_fork = &setup->forks[i];
        setup->philo[i].right_fork = &setup->forks[(i + 1) % philo_nbr];
    }
}

void	set_philos(t_setup *setup)
{
	int	i;
	int philo_nbr;

	i = -1;
	philo_nbr = setup->user_args->nbr_of_philo;
	while (++i < philo_nbr)
	{
		setup->philo[i].id = (i + 1);
		setup->philo[i].eat_count = 0;
		setup->philo[i].last_meal_time = setup->start_time;
		// // To prevent deadlock: even philos take right first, odd take left first
		set_philo_forks(setup, i);
		setup->philo[i].print_mutex = &setup->print_mutex;
		setup->philo[i].meal_mutex = &setup->meal_mutex;
		setup->philo[i].death_mutex = &setup->death_mutex;
		setup->philo[i].someone_died = &setup->someone_died;
		setup->philo[i].user_args = setup->user_args;
	}
}

void	init_philos(t_setup *setup)
{
	int	i;
	int	philo_nbr;

	philo_nbr = setup->user_args->nbr_of_philo;
	// >>> here cereate the philos and the forks (array of them)
	setup->philo = gc_malloc(setup->gc, sizeof(t_philo) * philo_nbr);
	setup->forks = gc_malloc(setup->gc, (sizeof(pthread_mutex_t) * philo_nbr));
	if (!setup->philo || !setup->forks)
		cleanup_and_exit(setup, "[-] Error: malloc failed.\n", 1);
	
	// >>> first -> set the thread(philos)
	set_philos(setup);

	// >>> second -> set the mutex(forks)
	i = -1;
	while (++i < philo_nbr)
		pthread_mutex_init(&setup->forks[i], NULL);	// >>> mutex to lock and unlock the fork
}

# include "_philo.h"

// • When a philosopher has finished eating, they put their forks back on the table and start sleeping.
// >>> what is have to do when i have one philo ???
// >>> void	singal_philo(t_setup *setup)
// >>> void	muliple_philo(t_setup *setup)
// >>> The number of philosophers and also the number of forks.
// >>> philo -> thread
// >>> fork -> mutex
// >>> thread must have two mutex????
// >>> The second argument in pthread_mutex_init(&mutex, NULL) is for mutex attributes.


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

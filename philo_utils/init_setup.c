# include "philo.h"

// done //

void	setup_user_args(t_setup *setup, char **argv)
{
	setup->user_args = gc_malloc(setup->gc, sizeof(t_user_args));
	if (!setup->user_args)
		cleanup_and_exit(setup, "[-] Error: malloc failed.\n", 1);
	setup->user_args->nbr_of_philo = ft_atoi(argv[1], setup);
	setup->user_args->time_to_die = ft_atoi(argv[2], setup);
	setup->user_args->time_to_eat = ft_atoi(argv[3], setup);
	setup->user_args->time_to_sleep = ft_atoi(argv[4], setup);
	setup->user_args->must_eat_meals = -1;
	if (argv[5])
		setup->user_args->must_eat_meals = ft_atoi(argv[5], setup);
}

t_setup	*init_setup(int argc, char **argv)
{
	t_setup	*setup;
	t_gc	*gc;

	gc = gc_init();
	setup = gc_malloc(gc, sizeof(t_setup));
	if (!gc || !setup)
		cleanup_and_exit(setup, "[-] Error: malloc failed.\n", 1);
	setup->gc = gc;
	input_parsing(argc, argv, setup);	// >>> parsing user input before get started
	setup->someone_died = 0;
	setup->all_ate_enough = 0;
	// >>> about the pthread_mutex_init <<<
	// >>> We use pthread_mutex_init to initialize a mutex, which protects access
	//     to a shared resource so that only one thread (philosopher) can access
	//     it at a time. This prevents race conditions
	// >>> When a philosopher wants to use a shared resource, it locks the mutex
	//     When it's done, it unlocks the mutex so other philosophers can use it
	// NOTE: if another philosopher (thread) tries to lock it, they will wait (block) until it is unlocked.
	pthread_mutex_init(&setup->print_mutex, NULL); // >>> Protects console output from being mixed between threads
	pthread_mutex_init(&setup->meal_mutex, NULL);  // >>> Protects access to `last_meal`; philosophers update it, monitor reads it
	pthread_mutex_init(&setup->death_mutex, NULL); // >>> Protects access to `someone_died` flag; ensures only one thread can read/write it at a time
	// Mutex -> (tool to synchronization and protect shared data)
	setup_user_args(setup, argv);
	setup->start_time = get_time_ms();
	setup->user_args->start_time = setup->start_time;
	init_philos(setup);
	return (setup);
}

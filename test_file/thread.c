# include "./srcs/_philo.h"

// here i will use a

// #define	NUMBER_THREADS 5
// pthread_mutex_t	mutex;
// int	counter = 0;

// void	*update_counter(void	*arg)
// {
// 	pthread_mutex_lock(&mutex);
// 	counter++;
// 	printf("thread %ld increnented counter to %d\n", (long)arg, counter);
// 	pthread_mutex_unlock(&mutex);
// 	return (NULL);
// }

// int	main()
// {
// 	size_t		i;
// 	pthread_t	threads[NUMBER_THREADS];
	
// 	i = 0;
// 	pthread_mutex_init(&mutex, NULL);
// 	while (i < NUMBER_THREADS)
// 	{
// 		pthread_create(&threads[i], NULL, update_counter, (void *)i);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < NUMBER_THREADS)
// 	{
// 		pthread_join(threads[i], NULL);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&mutex);
//     printf("Final counter value: %d\n", counter);
// 	return(0);
// }

// for (i = 0; i < philo_nbr; i++)
// 	pthread_mutex_init(&setup->forks[i], NULL);

// // Init shared mutexes
// pthread_mutex_init(&setup->print_mutex, NULL);
// pthread_mutex_init(&setup->meal_mutex, NULL);
// pthread_mutex_init(&setup->death_mutex, NULL);
// setup->someone_died = 0;




// t_setup	*init_setup(int argc, char **argv)
// {
// 	t_setup	*setup;
// 	t_gc	*gc;

// 	gc = gc_init();
// 	setup = gc_malloc(gc, sizeof(t_setup));
// 	if (!setup || !gc)
// 		return (cleanup_and_exit(setup, "[-] Error:"\
// 			" malloc failed.\n"), NULL);
// 	memset(setup, 0, sizeof(t_setup));
// 	setup->gc = gc;
// 	input_parsing(argc, argv, setup);
// 	setup_user_args(setup, argv);
// 	setup->start_time = get_time_ms();
// 	pthread_mutex_init(&setup->print_mutex, NULL);
// 	pthread_mutex_init(&setup->meal_mutex, NULL);
// 	pthread_mutex_init(&setup->death_mutex, NULL);
// 	setup->someone_died = 0;
// 	init_philos(setup);
// 	return (setup);
// }



// void	*routine(void *arg)
// {
// 	t_philo *philo = (t_philo *)arg;

// 	while (1)
// 	{
// 		// Check if someone died
// 		pthread_mutex_lock(philo->death_mutex);
// 		if (*philo->someone_died)
// 		{
// 			pthread_mutex_unlock(philo->death_mutex);
// 			break;
// 		}
// 		pthread_mutex_unlock(philo->death_mutex);

// 		// Eating
// 		take_forks(philo);
// 		pthread_mutex_lock(philo->meal_mutex);
// 		philo->last_meal_time = get_time_ms(); // shared var
// 		philo->eat_count++;
// 		pthread_mutex_unlock(philo->meal_mutex);

// 		// Print eating
// 		pthread_mutex_lock(philo->print_mutex);
// 		printf("%ld %d is eating\n", get_time_ms() - philo->setup->start_time, philo->id);
// 		pthread_mutex_unlock(philo->print_mutex);

// 		sleep_ms(philo->setup->user_args->time_to_eat);
// 		drop_forks(philo);

// 		// Sleep + print
// 		pthread_mutex_lock(philo->print_mutex);
// 		printf("%ld %d is sleeping\n", get_time_ms() - philo->setup->start_time, philo->id);
// 		pthread_mutex_unlock(philo->print_mutex);

// 		sleep_ms(philo->setup->user_args->time_to_sleep);

// 		// Think + print
// 		pthread_mutex_lock(philo->print_mutex);
// 		printf("%ld %d is thinking\n", get_time_ms() - philo->setup->start_time, philo->id);
// 		pthread_mutex_unlock(philo->print_mutex);
// 	}
// 	return (NULL);
// }

// void philosopher_1_routine(t_setup *setup)
// {
//     // Simulate a single philosopher eating and sleeping
//     printf("%ld 1 is eating\n", get_time_ms() - setup->start_time);
//     sleep_ms(setup->user_args->time_to_eat);  // Sleep after eating
//     printf("%ld 1 is sleeping\n", get_time_ms() - setup->start_time);
//     sleep_ms(setup->user_args->time_to_sleep); // Sleep again
//     printf("%ld 1 is thinking\n", get_time_ms() - setup->start_time); // Thinking
//     // Since no other philosopher, no need for mutexes or forks
// }

# include "philo.h"

// done //

// >>> loop thgouth all the philo to set the current time
// >>> set last_meal_time to start_time to avoid incorrect large elapsed time at start
// >>> or the compartion1
void	init_last_meal_time(t_setup *setup)
{
	int	i;
	int	philo_nbr;

	i = -1;
	philo_nbr = setup->user_args->nbr_of_philo;
	while (++i < philo_nbr)
		setup->philo[i].last_meal_time = setup->start_time;
}

// >>> pthread_create -> creates and starts threads immediately
// >>> pthread_create() requests the OS to create a new thread.
// >>> but actual execution order is not under your control
void	create_philo_threads(t_setup *setup)
{
	int	i;
	int	philo_nbr;

	i = -1;
	philo_nbr = setup->user_args->nbr_of_philo;
    while (++i < philo_nbr)
    {
		// printf("%d\n", i);
        if (pthread_create(&setup->philo[i].thread, NULL, 
                            philo_routine, &setup->philo[i]) != 0)
            cleanup_and_exit(setup, "[-] Error: phread_create failed\n", 1);
    }
}

// is it run under the order of the creation using the ptherad_join
// no — pthread_join does not make threads run in creation order.
// it only makes your main thread wait for another thread to finish.
// >>> NOTE: without the pthread_join the main process they will not wait
//		intel the threads finish there jobs.
void	set_pthread_join(t_setup *setup, pthread_t monitor)
{
	int	i;
	int	philo_nbr;

	i = -1;
	philo_nbr = setup->user_args->nbr_of_philo;
	while (++i < philo_nbr)
		pthread_join(setup->philo[i].thread, NULL);
	pthread_join(monitor, NULL);
}

void	start_simulation(t_setup *setup)
{
    pthread_t   monitor;

    setup->start_time = get_time_ms();
    setup->user_args->start_time = setup->start_time;
    
    // >>> init last_meal_time to start_time by defulte at the first time in array of the philos
	init_last_meal_time(setup);

    // >>> create and init the philos threads
    create_philo_threads(setup);

    // >>> give threads a small moment to initialize
    usleep(100);

    // >>> create monitor thread
    if (pthread_create(&monitor, NULL, monitor_routine, setup) != 0)
        cleanup_and_exit(setup, "[-] Error: monitor thread creation failed.\n", 1);
    
	// >>> wait the threads intel finish
    set_pthread_join(setup, monitor);
    if (setup->all_ate_enough)
        printf("All philosophers have eaten at least %d times\n", 
        setup->user_args->must_eat_meals);
}

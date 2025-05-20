# include "philo.h"

// done //

void print_status(t_philo *philo, char *status)
{
    // int someone_died;

    // First check if someone died without holding the print_mutex
    if (died_break(philo))
        return ;
    
    pthread_mutex_lock(philo->print_mutex);
    printf("%ld %d %s\n", 
        get_time_ms() - philo->user_args->start_time, 
        philo->id, 
        status);
    pthread_mutex_unlock(philo->print_mutex);
}

// >>> for a single philo <<<
void single_philo(t_philo *philo)
{
	long	start_wait;

    pthread_mutex_lock(philo->left_fork);
    print_status(philo, "has taken a fork");
    
    // For a lone philosopher, simply wait until death
    start_wait = get_time_ms();
    
    // Update last meal time when the philosopher takes the fork
    pthread_mutex_lock(philo->meal_mutex);
    philo->last_meal_time = start_wait;
    pthread_mutex_unlock(philo->meal_mutex);
    
    // Wait until the philosopher dies
    usleep(philo->user_args->time_to_die * 1000);
    
    // Release the fork before exiting
    pthread_mutex_unlock(philo->left_fork);
}

void	update_last_meal_time(t_philo *philo)
{
	// Update meal time ONCE, right at the start of eating
    pthread_mutex_lock(philo->meal_mutex);
    philo->last_meal_time = get_time_ms();
    pthread_mutex_unlock(philo->meal_mutex);
}

void	update_eat_count(t_philo *philo)
{
    // Update eat count after finishing eating
    pthread_mutex_lock(philo->meal_mutex);
    philo->eat_count++;
    pthread_mutex_unlock(philo->meal_mutex);
}

void *philo_routine(void *arg)
{
    t_philo	*philo;
    
    philo = (t_philo *)arg;
	philo_delays(philo);	// to KNOW why?
    while (1)
    {
		if (died_break(philo)) 
			break ;
        print_status(philo, "is thinking");
        if (philo->user_args->nbr_of_philo == 1)
        {
            single_philo(philo);
            break ;
        }
        pickup_forks(philo);
        print_status(philo, "is eating");
		update_last_meal_time(philo);
        ft_usleep(philo->user_args->time_to_eat);
        update_eat_count(philo);
		drop_the_forks(philo);
		drop_the_forks(philo);
		usleep(100); // Optional micro delay
        print_status(philo, "is sleeping");
        ft_usleep(philo->user_args->time_to_sleep);
    }
    return (NULL);
}

# include "philo.h"

void	philo_delays(t_philo *philo)
{
	// Stagger philosophers' start times to prevent race conditions
    // Make odd and even more distinct with different delays
    if (philo->id % 2 == 0)
	usleep(2000);
    else
	usleep(1000);
}

int	died_break(t_philo *philo)
{
	int	died;
	
	pthread_mutex_lock(philo->death_mutex);
	died = *philo->someone_died;
	pthread_mutex_unlock(philo->death_mutex);
	if (died)
		return (1);
	return (0);
}
// Odd/Even = required to avoid deadlock
void	pickup_forks(t_philo *philo)
{
	// Even philosophers pick up right fork first, odd pick up left first
	// This prevents deadlock by ensuring philosophers don't all grab the same fork first
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
}

void	drop_the_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
        
}

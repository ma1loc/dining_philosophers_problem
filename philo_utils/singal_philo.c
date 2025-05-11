# include "_philo.h"

void	singal_philo(t_setup *setup)
{
	printf("%ld 1 has taken a fork\n", get_time_ms() - setup->start_time);
	sleep_ms(setup->user_args->time_to_eat);
	printf("%ld 1 died\n", get_time_ms() - setup->start_time);
	cleanup_and_exit(setup, NULL, 0);
}
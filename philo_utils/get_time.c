# include "philo.h"

// done //


// size_t	get_time(void)
// {
// 	struct timeval	time;

// 	if (gettimeofday(&time, NULL) == -1)
// 		print_error(2, "Error : gettimeofday/n");
// 	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
// }

// int	ft_usleep(size_t milliseconds)
// {
// 	size_t	start;

// 	start = get_time();
// 	while (get_time() - start < milliseconds)
// 		usleep(100);
// 	return (0);
// }

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

// void sleep_ms(int ms)
void	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time_ms();
	while (get_time_ms() - start < milliseconds)
		usleep(100); // sleep 100us to avoid busy wait
}

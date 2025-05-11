# include "_philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void sleep_ms(int ms)
{
    usleep(ms * 1000);
}

# include "./srcs/_philo.h"

# define	NUMBER_THREAD 10

pthread_mutex_t	mutex;

void	*update_counter(void *arg)
{
	static int count;

	pthread_mutex_lock(&mutex);
	count++;
	printf("thread %ld increnented counter to %d\n", (long)arg, count);
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int	main()
{
	size_t	i;
	pthread_t		thread[NUMBER_THREAD];

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < NUMBER_THREAD)
	{
		pthread_create(&thread[i], NULL, update_counter, (void *)i);
		i++;
	}
	i = 0;
	while (i < NUMBER_THREAD)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}

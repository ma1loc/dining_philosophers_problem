/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:24:22 by yanflous          #+#    #+#             */
/*   Updated: 2025/05/23 17:24:23 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	if (died_break(philo))
		return ;
	pthread_mutex_lock(philo->print_mutex);
	printf("%ld %d %s\n",
		get_time_ms() - philo->user_args->start_time,
		philo->id, status);
	pthread_mutex_unlock(philo->print_mutex);
}

void	single_philo(t_philo *philo)
{
	long	start_wait;

	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	start_wait = get_time_ms();
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal_time = start_wait;
	pthread_mutex_unlock(philo->meal_mutex);
	usleep(philo->user_args->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
}

void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(philo->meal_mutex);
}

void	update_eat_count(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(philo->meal_mutex);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
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
		usleep(100);
		print_status(philo, "is sleeping");
		ft_usleep(philo->user_args->time_to_sleep);
	}
	return (NULL);
}

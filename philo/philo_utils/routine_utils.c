/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:24:38 by yanflous          #+#    #+#             */
/*   Updated: 2025/05/24 16:36:26 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	pickup_forks(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
}

void	drop_the_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	thinking_time(t_philo *philo)
{
	int	think_time;
	int	time_to_sleep;

	time_to_sleep = philo->user_args->time_to_sleep;
	if (philo->user_args->nbr_of_philo % 2 == 1)
	{
		think_time = (philo->user_args->time_to_eat * 2) - time_to_sleep;
		if (think_time > 0)
			ft_usleep(think_time / 2);
	}
}

void	operations(t_philo *philo)
{
	pickup_forks(philo);
	print_status(philo, "is eating");
	update_last_meal_time(philo);
	ft_usleep(philo->user_args->time_to_eat);
	update_eat_count(philo);
	drop_the_forks(philo);
	usleep(100);
	print_status(philo, "is sleeping");
	ft_usleep(philo->user_args->time_to_sleep);
	print_status(philo, "is thinking");
	thinking_time(philo);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:24:12 by yanflous          #+#    #+#             */
/*   Updated: 2025/05/23 17:24:13 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_someone_died(t_setup *setup)
{
	pthread_mutex_lock(&setup->death_mutex);
	if (setup->someone_died)
	{
		pthread_mutex_unlock(&setup->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&setup->death_mutex);
	return (0);
}

int	check_philo_died(t_setup *setup, long time_since_last_meal,
	long current_time, int i)
{
	if (time_since_last_meal > setup->user_args->time_to_die)
	{
		pthread_mutex_unlock(&setup->meal_mutex);
		pthread_mutex_lock(&setup->death_mutex);
		if (!setup->someone_died)
		{
			setup->someone_died = 1;
			pthread_mutex_unlock(&setup->death_mutex);
			pthread_mutex_lock(&setup->print_mutex);
			printf("%ld %d died\n",
				current_time - setup->start_time,
				setup->philo[i].id);
			pthread_mutex_unlock(&setup->print_mutex);
		}
		else
			pthread_mutex_unlock(&setup->death_mutex);
		return (1);
	}
	return (0);
}

int	check_all_ate_enough(t_setup *setup, int all_ate_enough)
{
	if (setup->user_args->must_eat_meals != -1 && all_ate_enough)
	{
		pthread_mutex_lock(&setup->death_mutex);
		setup->someone_died = 1;
		setup->all_ate_enough = 1;
		pthread_mutex_unlock(&setup->death_mutex);
		return (1);
	}
	return (0);
}

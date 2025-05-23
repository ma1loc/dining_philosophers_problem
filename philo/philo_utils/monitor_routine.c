/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:24:01 by yanflous          #+#    #+#             */
/*   Updated: 2025/05/23 17:24:03 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_check(t_setup *setup, int *all_ate_enough)
{
	int		i;
	long	current_time;
	long	time_since_last_meal;

	i = -1;
	while (++i < setup->user_args->nbr_of_philo)
	{
		pthread_mutex_lock(&setup->meal_mutex);
		current_time = get_time_ms();
		time_since_last_meal = current_time - setup->philo[i].last_meal_time;
		if (check_philo_died(setup, time_since_last_meal, current_time, i))
			return (1);
		if (setup->user_args->must_eat_meals != -1
			&& setup->philo[i].eat_count < setup->user_args->must_eat_meals)
			*all_ate_enough = 0;
		pthread_mutex_unlock(&setup->meal_mutex);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_setup	*setup;
	int		all_ate_enough;

	setup = (t_setup *)arg;
	usleep(1000);
	while (1)
	{
		all_ate_enough = 1;
		if (check_someone_died(setup))
			return (NULL);
		if (philo_check(setup, &all_ate_enough))
			return (NULL);
		if (check_all_ate_enough(setup, all_ate_enough))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:24:50 by yanflous          #+#    #+#             */
/*   Updated: 2025/05/23 17:24:53 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_last_meal_time(t_setup *setup)
{
	int	i;
	int	philo_nbr;

	i = -1;
	philo_nbr = setup->user_args->nbr_of_philo;
	while (++i < philo_nbr)
		setup->philo[i].last_meal_time = setup->start_time;
}

int	create_philo_threads(t_setup *setup)
{
	int	i;
	int	philo_nbr;

	i = -1;
	philo_nbr = setup->user_args->nbr_of_philo;
	while (++i < philo_nbr)
	{
		if (pthread_create(&setup->philo[i].thread, NULL,
				philo_routine, &setup->philo[i]) != 0)
			return (cleanup_and_exit(setup, "[-] Error: "\
					"phread_create failed\n", 1), 1);
	}
	return (0);
}

void	set_pthread_join(t_setup *setup, pthread_t monitor)
{
	int	i;
	int	philo_nbr;

	i = -1;
	philo_nbr = setup->user_args->nbr_of_philo;
	while (++i < philo_nbr)
		pthread_join(setup->philo[i].thread, NULL);
	pthread_join(monitor, NULL);
}

void	start_simulation(t_setup *setup)
{
	pthread_t	monitor;

	setup->start_time = get_time_ms();
	setup->user_args->start_time = setup->start_time;
	init_last_meal_time(setup);
	if (create_philo_threads(setup))
		return ;
	usleep(100);
	if (pthread_create(&monitor, NULL, monitor_routine, setup))
		return (cleanup_and_exit(setup, "[-] Error: "\
			"monitor thread creation failed.\n", 1), (void)0);
	set_pthread_join(setup, monitor);
	if (setup->all_ate_enough)
		printf("All philosophers have eaten at least %d times\n",
			setup->user_args->must_eat_meals);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_and_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:23:00 by yanflous          #+#    #+#             */
/*   Updated: 2025/05/23 17:23:02 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_cleanup(t_setup *setup)
{
	int	i;
	int	philo_nbr;

	i = -1;
	philo_nbr = setup->user_args->nbr_of_philo;
	pthread_mutex_destroy(&setup->print_mutex);
	pthread_mutex_destroy(&setup->meal_mutex);
	pthread_mutex_destroy(&setup->death_mutex);
	while (++i < philo_nbr)
		pthread_mutex_destroy(&setup->forks[i]);
}

void	cleanup_and_exit(t_setup *setup, char *msg, int destroy_flag)
{
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	if (destroy_flag)
		destroy_cleanup(setup);
	gc_destroy(setup->gc);
}

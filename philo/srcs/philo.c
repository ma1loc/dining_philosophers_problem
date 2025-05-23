/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:25:12 by yanflous          #+#    #+#             */
/*   Updated: 2025/05/23 17:25:13 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_setup	*setup;

	setup = init_setup(argc, argv);
	if (!setup)
		return (1);
	start_simulation(setup);
	cleanup_and_exit(setup, NULL, 1);
	return (0);
}
